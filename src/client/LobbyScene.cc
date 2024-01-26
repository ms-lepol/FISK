#include "LobbyScene.h"

#include "FiskColors.h"
#include "GameHub.h"
#include "LandEntity.h"
#include "LobbyPlayer.h"
#include "../common/NetworkProtocol.h"
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Keyboard.h>
#include <gf/Log.h>
#include <gf/Mouse.h>
#include <gf/Packet.h>
#include <gf/Serialization.h>
#include <gf/Texture.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <gf/MouseValues.h>
#include <iostream>

namespace fisk {

    namespace {
        constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
        constexpr int ViewRadius = 7;

        static constexpr float ZoomInFactor = 0.9f;
        static constexpr float ZoomOutFactor = 1.1f;

    }

    TitleEntity::TitleEntity(gf::Texture& texture) : texture(texture) {
        sprite.setTexture(texture);
        sprite.setPosition({ 0, 0 });
        direction = { 0, 1 };
    }
    void TitleEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        target.draw(sprite, states);
    }
    void TitleEntity::update(gf::Time time) {
        gf::Vector2f pos = sprite.getPosition();
        int speed = 10;
        
        if (pos.y > 20){
            direction.y = -1;
        }
        if (pos.y < 0){
            direction.y = 1;
        }

        pos.y += direction.y * speed * time.asSeconds();

        sprite.setPosition(pos);
    }

    LobbyScene::LobbyScene(GameHub& game)
        : gf::Scene(ViewSize)
          , m_game(game)
          , l_interact("Interact")
          , l_close("Close")
          , l_lobbyButton("Ready", game.resources.getFont("font/PixelSplitter-Bold.ttf"),30)
          , l_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
          , l_title(game.resources.getTexture("sprites/fiskTitle.png"))
          , l_player1(game.resources)
            , l_player2(game.resources)
            , l_player3(game.resources)
            , l_player4(game.resources)
          {
            
              setClearColor(HUDColor().backgroundColor);


              //HUD entities;

                l_HudEntities.addEntity(l_title);
                l_HudEntities.addEntity(l_player1);
                l_HudEntities.addEntity(l_player2);
                l_HudEntities.addEntity(l_player3);
                l_HudEntities.addEntity(l_player4);

              //HUD Buttons
                l_lobbyButton.setPosition({ ViewSize.x/2, ViewSize.y-100 });
                l_lobbyButton.setRadius(20);
                l_lobbyButton.setDefaultTextColor(HUDColor().backgroundColor);
                l_lobbyButton.setDefaultBackgroundColor(HUDColor().buttonColor);
                l_lobbyButton.setPadding(50);
                l_lobbyButton.setAnchor(gf::Anchor::Center);
                l_lobbyButton.setCallback([this, &game] {
                    std::cout << "Ready" << std::endl;
                    ClientReady data;
                    data.ready = true;
                    m_game.clientNetwork.send(data);
                });
                l_hudButtons.addWidget(l_lobbyButton);

                l_close.addKeycodeKeyControl(gf::Keycode::Escape);

                // Interact Action
                l_interact.addMouseButtonControl(gf::MouseButton::Left);

                addAction(l_interact);
                addAction(l_close);

          }

    void LobbyScene::doHandleActions([[maybe_unused]] gf::Window& window) {
        if (!isActive()) {
            return;
        }
        if (l_close.isActive()) {
            m_game.getWindow().close();
        }
        // Handle interact
        if (l_interact.isActive()) {
             
               
            l_hudButtons.pointTo(mousePos);
            l_hudButtons.triggerAction();


            l_interact.reset();
        }
    }

    void LobbyScene::doUpdate(gf::Time time) {
        gf::Event event;
        gf::Packet packeta;
        while (m_game.getWindow().pollEvent(event)){;
            if (event.type == gf::EventType::MouseMoved) {
                mousePos = event.mouseCursor.coords;
            }
        }

        l_HudEntities.update(time);
        //Handle packets
        if (m_game.clientNetwork.queue.poll(packeta)) {
            packeta.getType();
        }


    }

    void LobbyScene::doProcessEvent(gf::Event& event) {
        if (!isActive()) {
            return;
        }
        if (event.type == gf::EventType::MouseMoved) {
            mousePos = event.mouseCursor.coords;
        }
    }

    void LobbyScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {
        l_HudEntities.render(target, states);
        l_hudButtons.render(target, states);
        l_title.render(target, states);
        
        renderHudEntities(target, states);
    }

}
