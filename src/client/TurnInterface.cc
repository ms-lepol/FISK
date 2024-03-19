#include "TurnInterface.h"
#include "GameHub.h"
#include <algorithm>
#include <gf/Log.h>
#include <gf/Rect.h>
#include <iostream>



namespace fisk {

    TurnInterface::TurnInterface(GameHub& game, gf::ResourceManager& rm, gf::TextureAtlas& atlas) : 
        m_game(game),
        ressources(rm),
        atlas(atlas)
        {
        //Logic
        this->turn_order = 1;
        //Rendering
        this->m_spr.setPosition({0,0});
        position = {x_PosTI,y_PosTI};
        this->nb_player = this->m_game.clientNetwork.getGameModel().get_nb_players();
    }

    void TurnInterface::update(){
        changeTurn();
        this->nb_player = this->m_game.clientNetwork.getGameModel().get_nb_players();
    }

    void TurnInterface::changeTurn() {
        this->turn_order = m_game.clientNetwork.getGameModel().get_current_player();
        turn_order--;
    }

    void TurnInterface::setTurnOrder(gf::Color4f color) {
        if (color == PlayerColor().Yellow) {
            this->turn_order = 0;
        } else if (color == PlayerColor().Orange) {
            this->turn_order = 1;
        } else if (color == PlayerColor().Blue) {
            this->turn_order = 2;
        } else if (color == PlayerColor().Green) {
            this->turn_order = 3;
        } else {
            this->turn_order = -1;
        }
    }

    void TurnInterface::setPosition(gf::Vector2i position) {
        this->position = position;
    }

    void TurnInterface::setNbPlayer(unsigned nb_player) {
        this->nb_player = nb_player;
    }

    void TurnInterface::render(gf::RenderTarget& target, const gf::RenderStates& states) {

        //rendering block by block
        m_spr.setPosition(position);

        m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("upEdgeTI"));
        target.draw(m_spr, states);
        m_spr.move({0,32});

        auto disconnected = m_game.clientNetwork.getGameModel().get_disconnected();
        for(auto p : disconnected){
            gf::Log::debug("\t%lu\n", p);
        }
        for (int i = 0; i < nb_player; i++) {
            if(std::find(disconnected.begin(), disconnected.end(), i+1) == disconnected.end()){
            
                //rendering background
                m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("middleTI"));
                target.draw(m_spr, states);
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
                target.draw(m_spr, states);
                //rendering player portrait
                m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("portrait"));
                target.draw(m_spr, states);

                //rendering turn indicator
                if (i == turn_order) {
                    m_spr.move({48,0});
                    m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("turnIndicator"));
                    target.draw(m_spr, states);
                    m_spr.move({-48,0});
                }

                //next player position
                m_spr.move({-10,48});
            } 
        }


        m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("botEdgeTI"));
        target.draw(m_spr, states);


    }
}
