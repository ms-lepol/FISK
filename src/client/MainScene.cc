#include "MainScene.h" 

#include "GameHub.h"
#include "LandEntity.h"
#include "UnitSelector.h"
#include <cstddef>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Id.h>
#include <gf/Keyboard.h>
#include <gf/Mouse.h>
#include <gf/Shapes.h>
#include <gf/Texture.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <gf/MouseValues.h>
#include <iostream>
#include <mutex>
#include "../common/FiskColors.h"

namespace fisk {

    namespace {
        constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
        constexpr int ViewRadius = 7;

        static constexpr float ZoomInFactor = 0.9f;
        static constexpr float ZoomOutFactor = 1.1f;

    }

    CameraActions::CameraActions()
        : close("Close")
          , zoomIn("ZoomIn")
          , zoomOut("ZoomOut")
    {
    }

  MainScene::MainScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  
  , m_interact("Interact")
  , m_map(MapEntity(game,1))
  
  , m_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  , m_turnInterface(TurnInterface(0,game.resources,m_hudAtlas))
  , m_phaseIndicator(PhaseIndicator(gf::Color4f({0,1,0,0}),game,m_hudAtlas))
  , m_hudButtons(HudButtons(game.resources,m_hudAtlas,game))
  , m_unitSelector(game)
  {
   
    // Views
    


    //Rendering configuration

     int backgroundThickness = 5;
    
    background.setOutlineThickness(backgroundThickness);
    background.setSize({ViewSize.x-backgroundThickness*2,ViewSize.y-backgroundThickness*2});
    background.setPosition({static_cast<float>(backgroundThickness), static_cast<float>(backgroundThickness)});
    background.setColor(gf::Color::Transparent);
   

  
    
   
    m_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

    m_phaseIndicator.setColor(m_playerColor.Orange);


    //World entities
    m_WorldEntities.addEntity(m_map);

    //HUD entities

    m_HudEntities.addEntity(m_turnInterface);
    m_HudEntities.addEntity(m_phaseIndicator);
    m_HudEntities.addEntity(m_hudButtons);

    m_turnInterface.setPosition({static_cast<int>(ViewSize.x)-m_turnInterface.width- backgroundThickness,static_cast<int>(ViewSize.y)/2});
    m_phaseIndicator.setPosition({static_cast<int>(ViewSize.x)/2-m_phaseIndicator.width/2,static_cast<int>(ViewSize.y) - m_turnInterface.height-backgroundThickness-20});
    m_hudButtons.placeCardButton({static_cast<int>(ViewSize.x)/2-m_phaseIndicator.width - m_hudButtons.size,static_cast<int>(ViewSize.y)-m_hudButtons.size-backgroundThickness-10});
    m_hudButtons.placeEndPhaseButton({static_cast<int>(ViewSize.x)/2+ m_phaseIndicator.width/2+20,static_cast<int>(ViewSize.y)-backgroundThickness-50});

    // Camera Actions 
    m_cameraActions.close.addCloseControl();
    m_cameraActions.close.addKeycodeKeyControl(gf::Keycode::Escape);
    m_cameraActions.close.isActive();

    m_cameraActions.zoomIn.addScancodeKeyControl(gf::Scancode::Up);
    m_cameraActions.zoomIn.setContinuous();
    m_cameraActions.zoomOut.addScancodeKeyControl(gf::Scancode::Down);
    m_cameraActions.zoomOut.setContinuous();

    addAction(m_cameraActions.close);
    addAction(m_cameraActions.zoomIn);
    addAction(m_cameraActions.zoomOut);


    // Interact Action
    m_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(m_interact);

    m_HudEntities.addEntity(m_unitSelector);
    m_unitSelector.setPosition({static_cast<int>(ViewSize.x-m_unitSelector.getDimensions().x),static_cast<int>(ViewSize.y-m_unitSelector.getDimensions().y)});
    m_unitSelector.kill();
    m_unitSelector.setAlive();
  }

  void MainScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    
    // Handle camera
    if (m_cameraActions.close.isActive()) {
      m_game.getWindow().close();
    }

        // Handle interact
        if (m_interact.isActive()) {

            m_hudButtons.widg_container.pointTo(mousePos);
            m_hudButtons.widg_container.triggerAction();

            m_map.widg_container.pointTo(mousePos);
            m_map.widg_container.triggerAction();

            m_unitSelector.s_container.pointTo(mousePos);
            m_unitSelector.s_container.triggerAction();

            m_interact.reset();
        }
    }

  void MainScene::doUpdate(gf::Time time) {
    gf::Event event;
    while (m_game.getWindow().pollEvent(event)){;
      if (event.type == gf::EventType::MouseMoved) {
        mousePos = event.mouseCursor.coords;
      }
    }
    m_game.clientNetwork.update(); 

    std::lock_guard guard(m_game.clientNetwork.m_mutex);


        //Update the turn interface
        if (m_game.clientNetwork.hasGameModel()){
            auto& l_model = m_game.clientNetwork.getGameModel();
            m_turnInterface.setTurnOrder(l_model.get_player(l_model.get_current_player()).getColor4f());
            if (m_game.clientNetwork.hasPlayerList()){
                auto& l_playerList = m_game.clientNetwork.getPlayerList();
                m_turnInterface.setNbPlayer(l_playerList.players.size());
            }

            m_WorldEntities.update(time);
            m_HudEntities.update(time);
        }
    }


    void MainScene::doProcessEvent(gf::Event& event) {
        if (!isActive()) {
            return;
        }
        if (event.type == gf::EventType::MouseMoved) {
            mousePos = event.mouseCursor.coords;
        }
    }

  void MainScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {
    if (m_game.clientNetwork.hasGameModel()){
        auto& l_model = m_game.clientNetwork.getGameModel();
        
        background.setOutlineColor(l_model.get_player(m_game.clientNetwork.getClientId()).getColor4f());
        
    }
    
    target.draw(background, states);
   
    m_WorldEntities.render(target, states);
    m_HudEntities.render(target, states);
    
    //renderHudEntities(target, states);
  }

}
