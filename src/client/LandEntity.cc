#include "LandEntity.h" 
#include "GameHub.h"
#include <algorithm>
#include <gf/Anchor.h>
#include <gf/AnimatedSprite.h>
#include <gf/Id.h>
#include <gf/Log.h>
#include <gf/Time.h>
#include <sys/socket.h>
#include <mutex>


#define textOffset 1
#define landOutline 50


namespace fisk {
   

    LandEntity::LandEntity(std::string name, std::string sprite_path,gf::Vector2i position,gf::Vector2i positionText, GameHub& gm) : 
        name(name),
        game_hub(gm),
        m_texture(game_hub.resources.getTexture(sprite_path)),
        position(position),
        positionText(positionText),
        spr_widg(gf::SpriteWidget())
        {

        
        //Logic
       auto& model = game_hub.clientNetwork.getGameModel();
       prev_owner = gf::InvalidId;
        //Rendering
        land_explosion.addTileset(game_hub.resources.getTexture("sprites/land_explosion.png"), {3,4}, gf::seconds(2.0f/5.0f), 12);
        land_explosion.setLoop(false);
        
        spr_widg.setDefaultSprite(m_texture, gf::RectF::fromMinMax({0,0}, {1,1}));
        spr_widg.setPosition(position);
        spr_widg.setCallback([this] {
            std::lock_guard guard(game_hub.clientNetwork.m_mutex);
            gf::Log::info("LandEntity %s : clicked\n", this->name.c_str());
            //
            auto& map = game_hub.mainScene.m_map;
            auto& model = game_hub.clientNetwork.getGameModel();
            //
            if(model.get_current_player() != game_hub.clientNetwork.getClientId()) {
                gf::Log::info("(CLIENT GAME) This is not your turn to play\n");
                return;
            }
            //
            map.select(this);
            bool is_curr_land_owned = (model.get_land_by_name(map.curr_selection->getName()).getOwner() == game_hub.clientNetwork.getClientId());
            gf::Log::debug("Current land owned ? %i\n", is_curr_land_owned);
            //
            switch (model.get_current_phase()) {
                case TurnPhase::Fortify:
                    if(!is_curr_land_owned){
                        gf::Log::warning("(CLIENT GAME) Cannot fortify a land not owned by the player.\n");
                        map.reset_selections();
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    this->game_hub.mainScene.m_unitSelector.show();
                    gf::Log::debug("Showing unitSelector...\n");
                    //
                    break;
                case TurnPhase::Attack: {
                    if(map.old_selection == nullptr) { // First selection
                        if(!is_curr_land_owned){
                            map.reset_selections();
                            gf::Log::warning("(CLIENT GAME) Cannot attack from a land not owned\n");
                            this->game_hub.mainScene.m_unitSelector.hide();
                            break;
                        }
                        // First selection is an owned land
                        gf::Log::info("(CLIENT GAME) Waiting for second selection\n");
                        //
                        break;
                    }
                    if(model.get_land_by_name(map.old_selection->getName()).getOwner() != game_hub.clientNetwork.getClientId()) {
                        // First selection is not owned, have to reset because we dont keep 3 selection in memory
                        map.reset_selections();
                        gf::Log::warning("(CLIENT GAME) Cannot attack from a land not owned\n");
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    if(is_curr_land_owned){
                        // Re-clicking on a owned land should just switch selections
                        map.old_selection = map.curr_selection;
                        gf::Log::warning("(CLIENT GAME) Clicking again on a owned land\n");
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    // Check neighbours
                    if(!model.is_neighbour(model.get_land_id_by_name(map.old_selection->getName()), model.get_land_id_by_name(map.curr_selection->getName()))) {
                        gf::Log::warning("(CLIENT GAME) The selected land to attack is not a neighbour of the attacking land.\n");
                        map.curr_selection = map.old_selection;
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    if(model.get_land_by_name(map.old_selection->getName()).getNb_units() <= 1){
                        gf::Log::warning("(CLIENT GAME) First selection does not have enough units to attack !\n");
                        map.curr_selection = map.old_selection;
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    // Selections are OK for an attack
                    this->game_hub.mainScene.m_unitSelector.show();
                    gf::Log::debug("(CLIENT GAME) Showing unitSelector...\n");
                    break;
                }
                case TurnPhase::Reinforce:
                    if(map.old_selection == nullptr) { // First selection
                        if(!is_curr_land_owned){
                            map.reset_selections();
                            gf::Log::warning("(CLIENT GAME) Cannot reinforce a land not owned\n");
                            this->game_hub.mainScene.m_unitSelector.hide();
                            break;
                        }
                        // First selection is an owned land
                        gf::Log::info("(CLIENT GAME) Waiting for second selection\n");
                        //
                        break;
                    }
                    if(model.get_land_by_name(map.old_selection->getName()).getOwner() != game_hub.clientNetwork.getClientId()) {
                        // First selection is not owned, have to reset because we dont keep 3 selection in memory
                        map.reset_selections();
                        gf::Log::warning("(CLIENT GAME) Cannot reinforce a land not owned\n");
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    if(!is_curr_land_owned){
                        // Re-clicking on a non owned land
                        map.old_selection = map.curr_selection;
                        gf::Log::warning("(CLIENT GAME) Clicking on a non owned land\n");
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    if (model.get_land_by_name(map.old_selection->getName()).getNb_units() <= 1){
                        gf::Log::warning("(CLIENT GAME) First selection does not have enough units to reinforce !\n");
                        map.reset_selections();
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    // Check if there is a path between the two lands clicked
                    if(!model.are_lands_on_same_territory(model.get_land_id_by_name(map.old_selection->getName()), model.get_land_id_by_name(map.curr_selection->getName()))) {
                        gf::Log::warning("(CLIENT GAME) The two land are not connected\n");
                        map.reset_selections();
                        this->game_hub.mainScene.m_unitSelector.hide();
                        break;
                    }
                    // Selections are OK for a reinforce
                    this->game_hub.mainScene.m_unitSelector.show();
                    gf::Log::debug("(CLIENT GAME) Showing unitSelector...\n");
                    break;
                case TurnPhase::End:
                default:
                    gf::Log::warning("LandEntity SetCallback Switch, should not be here\n");
                    break;
            }
        }); 
    }

    gf::Color4f LandEntity::getColor() {
        std::lock_guard guard(game_hub.clientNetwork.m_mutex);
        if(game_hub.clientNetwork.hasGameModel()) {
            PlayerId owner = game_hub.clientNetwork.getGameModel().get_land_by_name(name).getOwner();
            if(owner != gf::InvalidId) {
                return game_hub.clientNetwork.getGameModel().get_player(owner).getColor4f();
            }
        }
        return PlayerColor().Neutral;
    }

    std::string LandEntity::getName(){
        return name;
    }

    void LandEntity::update(gf::Time time) {
        std::lock_guard guard(game_hub.clientNetwork.m_mutex);
        auto& model = game_hub.clientNetwork.getGameModel();
        PlayerId owner = model.get_land_by_name(name).getOwner();
        if(owner != prev_owner) {
            changed_owner = true;
            prev_owner = owner;
            gf::Log::info("LandEntity %s : owner changed\n", name.c_str());
        }
    }

    void LandEntity::render(gf::RenderTarget& target,gf::RenderStates states) {
        
        if (getColor()!=gf::Color::Transparent){
            spr_widg.setColor(getColor());
        }
        
        target.draw(spr_widg, states);
        gf::Font& font = game_hub.resources.getFont("font/PixelSplitter-Bold.ttf");
        unsigned nb_units;
        {
            std::lock_guard guard(game_hub.clientNetwork.m_mutex);
            nb_units = game_hub.clientNetwork.hasGameModel() ? game_hub.clientNetwork.getGameModel().get_land_by_name(name).getNb_units() : 0;
        }
        std::string text = std::to_string(nb_units);
        if (nb_units < 10) text = "0" + text;
        gf::Text txt(text, font, 10);
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText+gf::Vector2i({0,1}));
        target.draw(txt,states);
        if (changed_owner){
            renderAnimation(target, states);
        }
    }


    //Change the color to a dark version if selected
    void LandEntity::renderSelected(gf::RenderTarget& target, gf::RenderStates states){
       
        gf::Color4f color;

        if (getColor()==LandColor().Neutral){
            color = LandColor().DarkNeutral;
        }
        if (getColor()==LandColor().Orange){
            color = LandColor().DarkOrange;
            
        }
        if (getColor()==LandColor().Blue){
            color = LandColor().DarkBlue;
        }
        if (getColor()==LandColor().Green){
            color = LandColor().DarkGreen;
            
        }
        if (getColor()==LandColor().Yellow){
            color = LandColor().DarkYellow;
            
        }
        spr_widg.setColor(color);
    
        target.draw(spr_widg, states);
        gf::Font& font = game_hub.resources.getFont("font/PixelSplitter-Bold.ttf");
        unsigned nb_units;
        {
            std::lock_guard guard(game_hub.clientNetwork.m_mutex);
            nb_units = game_hub.clientNetwork.hasGameModel() ? game_hub.clientNetwork.getGameModel().get_land_by_name(name).getNb_units() : 0;
        }
        std::string text = std::to_string(nb_units);
        if (nb_units < 10) text = "0" + text;
        gf::Text txt(text, font, 10);
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText+gf::Vector2i({0,1}));
        target.draw(txt,states);
        if (changed_owner){
            renderAnimation(target, states);
        }
    }

    void LandEntity::renderHinted(gf::RenderTarget& target, gf::RenderStates states){
         gf::Color4f color;

        if (getColor()==LandColor().Neutral){
            color = LandColor().LightNeutral;
        }
        if (getColor()==LandColor().Orange){
            color = LandColor().LightOrange;
            
        }
        if (getColor()==LandColor().Blue){
            color = LandColor().LightBlue;
        }
        if (getColor()==LandColor().Green){
            color = LandColor().LightGreen;
            
        }
        if (getColor()==LandColor().Yellow){
            color = LandColor().LightYellow;
            
        }
        spr_widg.setColor(color);
        target.draw(spr_widg, states);
        gf::Font& font = game_hub.resources.getFont("font/PixelSplitter-Bold.ttf");
        unsigned nb_units;
        {
            std::lock_guard guard(game_hub.clientNetwork.m_mutex);
            nb_units = game_hub.clientNetwork.hasGameModel() ? game_hub.clientNetwork.getGameModel().get_land_by_name(name).getNb_units() : 0;
        }
        std::string text = std::to_string(nb_units);
        if (nb_units < 10) text = "0" + text;
        gf::Text txt(text, font, 10);
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText+gf::Vector2i({0,1}));
        target.draw(txt,states);
        if (changed_owner){
            renderAnimation(target, states);
        }
    }

    void LandEntity::renderAnimation(gf::RenderTarget& target, gf::RenderStates states){
        gf::AnimatedSprite land_explosion_spr;
        land_explosion_spr.setColor(gf::Color::Red);
        land_explosion_spr.setAnchor(gf::Anchor::Center);
        land_explosion_spr.setPosition(position+positionText-gf::Vector2i({32,32}));
        land_explosion_spr.setAnimation(land_explosion);
        land_explosion.update(gf::seconds(1.0f/12.0f));
        gf::Log::info("LandEntity %s : rendering animation\n", name.c_str());
        
        target.draw(land_explosion_spr, states);
        if (land_explosion.isFinished()){
            changed_owner = false;
        }
    }
}