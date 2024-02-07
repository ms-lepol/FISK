#include "LandEntity.h" 
#include "GameHub.h"
#include <gf/Id.h>
#include <gf/Log.h>
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
        selected = false;
        //Rendering
        spr_widg.setDefaultSprite(m_texture, gf::RectF::fromMinMax({0,0}, {1,1}));
        spr_widg.setPosition(position);
        spr_widg.setCallback([this] {
            std::lock_guard guard(game_hub.clientNetwork.m_mutex);
            gf::Log::info("LandEntity %s : clicked\n", this->name.c_str());
            //
            auto& map = game_hub.mainScene.m_map;
            auto& model = game_hub.clientNetwork.getGameModel();
            //
            map.select(this);
            gf::Log::debug("Selecting...\n");
            auto& curr_land = model.get_land_by_name(map.curr_selection->name);
            gf::Log::debug("ct ici la segfault :3...\n");
            //

            this->game_hub.mainScene.m_unitSelector.show();
            gf::Log::debug("Showing unitSelector...\n");
            selected = !selected;
            //
            gf::Log::debug("Before switch...\n");
            switch(model.get_current_phase()){
                case TurnPhase::Fortify:
                    gf::Log::debug("Fortify...");
                    if(curr_land.getOwner() != game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) Current selection is not owned by player\n");
                    }
                    else {
                        ClientGameSendFortify fortify;
                        fortify.land_id = model.get_land_id_by_name(map.curr_selection->name);
                        fortify.nb = 1; // Need to change for the selector
                        //
                        game_hub.clientNetwork.send(fortify);
                    }
                    selected = false;
                    map.reset_selections();
                    break;
                case TurnPhase::Attack:
                    gf::Log::debug("Attack...\n");
                    if(map.old_selection == nullptr){
                        gf::Log::warning("(GAME CIENT) Waiting for a second land to be chosen\n");
                        break;
                    }
                    if(model.get_land_by_name(map.old_selection->name).getOwner() != game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) First selection is not owned by player\n");
                    }
                    else if (model.get_land_by_name(map.old_selection->name).getNb_units() <= 1){
                        gf::Log::warning("(CLIENT GAME) First selection does not have enough units to attack !\n");
                    }
                    else if(curr_land.getOwner() == game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) Second selection is owned by player\n");
                    }
                    else{
                        ClientGameSendAttack attack;
                        attack.attacking_land_id = model.get_land_id_by_name(map.old_selection->name);
                        attack.defending_land_id = model.get_land_id_by_name(map.curr_selection->name);
                        unsigned nb_units = model.get_land_by_name(map.old_selection->name).getNb_units();
                        // Automatic choice of dice (can be replaced with selector)
                        unsigned n = 3;
                        if(nb_units <= 4) n = nb_units-1;
                        if(n <= 1) n = 1;
                        attack.attacking_nb_dice = n;
                        //
                        game_hub.clientNetwork.send(attack);
                    }
                    selected = false;
                    map.reset_selections();
                    break;
                case TurnPhase::Reinforce:
                    gf::Log::debug("Reinforce...\n");
                    selected = false;
                    map.reset_selections();
                    break;
                case TurnPhase::End:
                    gf::Log::debug("End...\n");
                    selected = false;
                    map.reset_selections();
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

    bool LandEntity::isSelected(){
        return selected;
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
    }


    //Draw an outline if selected
    void LandEntity::renderSelected(gf::RenderTarget& target, gf::RenderStates states){
        if (selected){
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
    }
}
