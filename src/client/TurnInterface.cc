#include "TurnInterface.h"
#include <gf/Rect.h>
#include <iostream>



namespace fisk {

    TurnInterface::TurnInterface(unsigned nb_player, gf::ResourceManager& rm, gf::TextureAtlas& atlas) : 
        nb_player(nb_player),
        ressources(rm),
        atlas(atlas)
        {
        //Logic
        this->turn_order = 0;
        //Rendering
        this->m_spr.setPosition({100,y_PosTI});
    }

    void TurnInterface::changeTurn() {
        this->turn_order = (this->turn_order + 1) % this->nb_player;
    }

    void TurnInterface::render(gf::RenderTarget& target) {
        gf::RenderStates state;
        //rendering block by block

        m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("upEdgeTI"));
        target.draw(m_spr, state);
        m_spr.move({0,32});

        for (int i = 0; i < nb_player; i++) {
            //rendering background
            m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("middleTI"));
            target.draw(m_spr, state);
            m_spr.move({10,0});
            //rendering player circle
            std::string playerCircleTI;
            switch (i) {
                case 0:
                    playerCircleTI = "yellowCircle";
                    break;
                case 1:
                    playerCircleTI = "orangeCircle";
                    break;
                case 2:
                    playerCircleTI = "blueCircle";
                    break;
                case 3:
                    playerCircleTI = "GreenCircle";
                    break;
                default:
                    playerCircleTI = "GreenCircle";
                    break;
            
            }
            m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect(playerCircleTI));
            target.draw(m_spr, state);
            //rendering player portrait
            m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("portrait"));
            target.draw(m_spr, state);

            //rendering turn indicator
            if (i == turn_order) {
                m_spr.move({48,0});
                m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("turnIndicator"));
                target.draw(m_spr, state);
                m_spr.move({-48,0});
            }

            //next player position
            m_spr.move({-10,48});
        }


        m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("botEdgeTI"));
        target.draw(m_spr, state);


        m_spr.setPosition({x_PosTI,y_PosTI});
    }
}
