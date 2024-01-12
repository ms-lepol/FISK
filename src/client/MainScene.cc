#include "MainScene.h"

#include "GameHub.h"
#include <gf/Color.h>
#include <gf/Keyboard.h>
#include <gf/Texture.h>
#include <gf/TextureAtlas.h>
#include <iostream>

namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.8f;
    static constexpr float ZoomOutFactor = 1.25f;

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
  , m_WorldView({ 0.0f, 0.0f }, ViewSize)
  , adaptor(game.getRenderer(), m_WorldView)
  , m_map(MapEntity(game.resources,1))
  , m_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml"))
  , m_turnInterface(TurnInterface(2,game.resources,m_hudAtlas))
  , m_phaseIndicator(PhaseIndicator(gf::Color4f({0,1,0,0}),game.resources,m_hudAtlas))
  , m_hudButtons(HudButtons(game.resources,m_hudAtlas))
  {
    /* auto ltViewport = gf::RectF::fromPositionSize({ 0.0f, 0.0f }, { 0.5f, 1.0f });
    m_WorldView.setViewport(ltViewport);
    m_HudView.setViewport(ltViewport);
     */
    addView(m_WorldView);
    addView(m_HudView);
    
    m_HudView.setSize(m_game.getWindow().getSize());
    
    m_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

 
    m_WorldEntities.addEntity(m_map);
    m_HudEntities.addEntity(m_turnInterface);
    m_phaseIndicator.setColor(m_playerColor.Orange);
    m_HudEntities.addEntity(m_phaseIndicator);
    m_HudEntities.addEntity(m_hudButtons);
    
    m_turnInterface.setPosition({static_cast<int>(m_HudView.getSize().x)-m_turnInterface.width,static_cast<int>(m_HudView.getSize().y)/2});
    m_phaseIndicator.setPosition({static_cast<int>(m_HudView.getSize().x)/2-m_phaseIndicator.width/2,static_cast<int>(m_HudView.getSize().y) - m_turnInterface.height});
    
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

    m_WorldView.setCenter({ViewSize.x/2,ViewSize.y/2  });
    m_WorldView.setSize(ViewSize);
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
  }

  void MainScene::doUpdate(gf::Time time) {
   /*  if (m_game.state.status == GameStatus::Victory) {
      m_game.replaceScene(m_game.victory);
    } */

    m_WorldEntities.update(time);
    m_HudEntities.update(time);


  }

  void MainScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {
    target.setView(m_WorldView);
    m_WorldEntities.render(target, states);
    target.setView(m_HudView);
    m_HudEntities.render(target, states);
    
    renderHudEntities(target, states);
  }

}