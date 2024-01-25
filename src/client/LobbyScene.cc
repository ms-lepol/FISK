#include "LobbyScene.h"

#include "GameHub.h"
#include "LandEntity.h"
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Keyboard.h>
#include <gf/Mouse.h>
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


    LobbyScene::LobbyScene(GameHub& game)
        : gf::Scene(ViewSize)
          , m_game(game)
          , l_interact("Interact")
          , l_lobbyButton("Ready", game.resources.getFont("font/PixelSplitter-Bold.ttf"),30)
          {

              setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));



              //World entities

              //HUD entities

              //HUD Buttons
                l_lobbyButton.setPosition({ 100, 100 });
                l_lobbyButton.setBackgroundOutlineThickness(10);
                l_lobbyButton.setDefaultBackgroundOutlineColor(gf::Color::fromRgba32(0x000000FF));
                l_lobbyButton.setAnchor(gf::Anchor::Center);
                l_lobbyButton.setCallback([this] {
                    std::cout << "Ready" << std::endl;
                    //MESSAGE ICI MIMIL
                });
                l_hudButtons.addWidget(l_lobbyButton);



              // Interact Action
              l_interact.addMouseButtonControl(gf::MouseButton::Left);

              addAction(l_interact);

          }

    void LobbyScene::doHandleActions([[maybe_unused]] gf::Window& window) {
        if (!isActive()) {
            return;
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
        while (m_game.getWindow().pollEvent(event)){;
            if (event.type == gf::EventType::MouseMoved) {
                mousePos = event.mouseCursor.coords;
            }
        }

        l_WorldEntities.update(time);
        l_HudEntities.update(time);


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
        l_WorldEntities.render(target, states);
        l_HudEntities.render(target, states);
        l_hudButtons.render(target, states);

        renderHudEntities(target, states);
    }

}
