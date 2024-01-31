#include "LobbyScene.h"

#include "ClientNetwork.h"
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
                    data.ready = !game.clientNetwork.isClientReady();
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
        m_game.clientNetwork.update(); 
        resetPlayers();

        //Update the players list
        if (m_game.clientNetwork.hasPlayerList()) {
            auto& l_players = m_game.clientNetwork.getPlayerList();
            for (auto& player : l_players.players) {
                addPlayer(player.id, player.name);
                setPlayerReady(player.id, player.ready);
            }
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

    //Use a lambda
     void LobbyScene::addPlayer(gf::Id id_player, std::string name){

        if (id_player == l_player1.getId() || id_player == l_player2.getId() || id_player == l_player3.getId() || id_player == l_player4.getId()){
            return;
        }

        if (l_player1.getId() == 0){
            l_player1.setName(name);
            l_player1.setPlotIsFilled(true);
            l_player1.setId(id_player);
        } else if (l_player2.getId() == 0){
            l_player2.setName(name);
            l_player2.setPlotIsFilled(true);
            l_player2.setId(id_player);
        } else if (l_player3.getId() == 0){
            l_player3.setName(name);
            l_player3.setPlotIsFilled(true);
            l_player3.setId(id_player);
        } else if (l_player4.getId() == 0){
            l_player4.setName(name);
            l_player4.setPlotIsFilled(true);
            l_player4.setId(id_player);
        }
    }

    //Use a lambda
    void LobbyScene::setPlayerReady(gf::Id id_player, bool isReady){
        if (id_player == l_player1.getId()){
            l_player1.setReady(isReady);
        } else if (id_player == l_player2.getId()){
            l_player2.setReady(isReady);
        } else if (id_player == l_player3.getId()){
            l_player3.setReady(isReady);
        } else if (id_player == l_player4.getId()){
            l_player4.setReady(isReady);
        }
    }

    void LobbyScene::setPlayerPlot(gf::Id id_player, bool plotIsFilled){
        if (id_player == l_player1.getId()){
            l_player1.setPlotIsFilled(plotIsFilled);
        } else if (id_player == l_player2.getId()){
            l_player2.setPlotIsFilled(plotIsFilled);
        } else if (id_player == l_player3.getId()){
            l_player3.setPlotIsFilled(plotIsFilled);
        } else if (id_player == l_player4.getId()){
            l_player4.setPlotIsFilled(plotIsFilled);
        }
    }

    void LobbyScene::setPlayerName(gf::Id id_player, std::string name){
        if (id_player == l_player1.getId()){
            l_player1.setName(name);
        } else if (id_player == l_player2.getId()){
            l_player2.setName(name);
        } else if (id_player == l_player3.getId()){
            l_player3.setName(name);
        } else if (id_player == l_player4.getId()){
            l_player4.setName(name);
        }
    }

    void LobbyScene::resetPlayers(){
        l_player1.reset();
        l_player2.reset();
        l_player3.reset();
        l_player4.reset();
    }

   

}
