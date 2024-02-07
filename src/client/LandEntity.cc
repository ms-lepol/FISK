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
            //
            switch (model.get_current_phase()) {
                case TurnPhase::Attack:
                case TurnPhase::Reinforce:
                    if(map.old_selection == nullptr) break;
                case TurnPhase::Fortify:
                    this->game_hub.mainScene.m_unitSelector.show();
                    gf::Log::debug("Showing unitSelector...\n");
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
    }
}