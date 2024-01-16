#include "MainScene.h"

#include "GameHub.h"
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

   PlayerColor::PlayerColor()
   : Orange({(float)255/255,(float)140/255,(float)92/255,1})
   , Blue({(float)99/255,(float)155/255,(float)255/255,1})
   , Green({(float)134/255,(float)192/255,(float)108/255,1})
   , Yellow({(float)251/255,(float)239/255,(float)8/255,1})
   {

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
  , m_WorldView({ViewSize.x/2,ViewSize.y/2 }, ViewSize)
  , adaptor(game.getRenderer(), m_WorldView)
  , m_interact("Interact")
  , m_map(MapEntity(game.resources,1))
  
  , m_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  , m_turnInterface(TurnInterface(4,game.resources,m_hudAtlas))
  , m_phaseIndicator(PhaseIndicator(gf::Color4f({0,1,0,0}),game.resources,m_hudAtlas))
  , m_hudButtons(HudButtons(game.resources,m_hudAtlas))
  {
   
    // Views
    addView(m_WorldView);
    addView(m_HudView);
    
    //Rendering configuration
    m_HudView.setSize(m_game.getWindow().getSize()); 
    m_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

    m_phaseIndicator.setColor(m_playerColor.Orange);

   
    //World entities
    m_WorldEntities.addEntity(m_map);

    //HUD entities

    m_HudEntities.addEntity(m_turnInterface);
    m_HudEntities.addEntity(m_phaseIndicator);
    m_HudEntities.addEntity(m_hudButtons);

    std::cout << "hud size: " << m_HudView.getSize().x << " "<< m_HudView.getSize().y<<std::endl;
    
    m_turnInterface.setPosition({static_cast<int>(ViewSize.x)-m_turnInterface.width,static_cast<int>(ViewSize.y)/2});
    m_phaseIndicator.setPosition({static_cast<int>(ViewSize.x)/2-m_phaseIndicator.width/2,static_cast<int>(ViewSize.y) - m_turnInterface.height});
    m_hudButtons.placeCardButton({static_cast<int>(ViewSize.x)/2-m_phaseIndicator.width - m_hudButtons.size,static_cast<int>(ViewSize.y)-m_hudButtons.size});


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


    m_WorldView.setInitialFramebufferSize(m_game.getRenderer().getSize());
    //m_HudView.setSize(ViewSize);
    m_HudView.setInitialFramebufferSize(m_game.getRenderer().getSize());
  }

  void MainScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    // Handle interact
    
    // Handle camera
    if (m_cameraActions.close.isActive()) {
      m_game.getWindow().close();
    }
    if (m_cameraActions.zoomIn.isActive()) {
      m_WorldView.zoom(ZoomInFactor);
    }
    if (m_cameraActions.zoomOut.isActive()) {
      m_WorldView.zoom(ZoomOutFactor);
    }

    // Handle interact
    if (m_interact.isActive()) {
      
      m_hudButtons.widg_container.pointTo(mousePos);
      m_hudButtons.widg_container.triggerAction();
      
      m_map.widg_container.pointTo(mousePos);
      m_map.widg_container.triggerAction();

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

    m_WorldEntities.update(time);
    m_HudEntities.update(time);


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
    target.setView(m_WorldView);
    target.setView(m_HudView);

    m_WorldEntities.render(target, states);
    m_HudEntities.render(target, states);
    
    renderHudEntities(target, states);
  }

}