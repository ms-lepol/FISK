
#include "HudButtons.h"
#include "GameHub.h"
#include <gf/Log.h>



namespace fisk {

    HudButtons::HudButtons(gf::ResourceManager& rm, gf::TextureAtlas& atlas, GameHub& game) : 
        m_game(game),
        ressources(rm), 
        atlas(atlas),
        widg_card(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("buttonCard"),atlas.getTextureRect("buttonCard"),atlas.getTextureRect("buttonCard"))),
        widg_quit(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("buttonQuit"),atlas.getTextureRect("buttonQuit"),atlas.getTextureRect("buttonQuit"))),
        widg_endPhase("End Attack",rm.getFont("font/PixelSplitter-Bold.ttf"),20)
    {
        //Logic

        //Rendering


        widg_card.setPosition({0,0});
        widg_quit.setPosition({10,10});

        widg_quit.setCallback([this] {
            gf::Log::info("QuitButton clicked\n");
            m_game.clientNetwork.disconnect();
            m_game.getWindow().close();
        });
    

        widg_endPhase.setCallback([this] {
        });
        widg_endPhase.setDefaultBackgroundColor(HUDColor().buttonColor);
        widg_endPhase.setDefaultTextColor(HUDColor().backgroundColor);
        widg_endPhase.setPadding(20.0f);
        widg_endPhase.setRadius(10.0f);
        widg_endPhase.setPosition({202,50});

        //Logic
        widg_card.setCallback([this] {
                callbackCardButton();
                });

        widg_container.addWidget(widg_card);
        widg_container.addWidget(widg_quit);
        widg_container.addWidget(widg_endPhase);

    }

    void HudButtons::callbackCardButton() {
        //Logic
        gf::Log::info("CardButton clicked\n");
        m_game.pushScene(m_game.cardScene);

    }

    void HudButtons::placeCardButton(gf::Vector2i position) {
        widg_card.setPosition(position);
    }

    void HudButtons::placeEndPhaseButton(gf::Vector2i position) {
        widg_endPhase.setPosition(position);
    }

    void HudButtons::initTextures(){
        widg_card.setDefaultSprite(atlas.getTexture(),atlas.getTextureRect("buttonCard"));
        widg_quit.setDefaultSprite(atlas.getTexture(),atlas.getTextureRect("buttonQuit"));

    }

    void HudButtons::update(gf::Time time) {
        //Logic
          if (m_game.clientNetwork.hasGameModel()){
            auto& l_model = m_game.clientNetwork.getGameModel();
            if (l_model.get_current_phase() == TurnPhase::Attack 
                && l_model.get_current_player() == m_game.clientNetwork.getClientId()){
                widg_endPhase.setString("End Attack");
                widg_endPhase.setCallback([this] {
                    gf::Log::debug("Ending attack phase...\n");
                    ClientGameEndAttack end;
                    m_game.clientNetwork.send(end);
                });
                widg_container.addWidget(widg_endPhase);
           } else if (l_model.get_current_phase() == TurnPhase::Reinforce 
                && l_model.get_current_player() == m_game.clientNetwork.getClientId()){
                 widg_endPhase.setString("End Reinforce");
                 widg_endPhase.setCallback([this] {
                    gf::Log::debug("Ending reinforce phase...\n");
                    ClientGameEndReinforce end;
                    m_game.clientNetwork.send(end);
                });
                widg_container.addWidget(widg_endPhase);
           } else {
                widg_container.removeWidget(&widg_endPhase);
           }
            
        }
    }

    void HudButtons::render(gf::RenderTarget& target, const gf::RenderStates& states) {
      
        //rendering block by block
        widg_container.render(target,states);
    }

}
