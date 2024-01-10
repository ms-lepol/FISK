#include "MainScene.h"

#include "GameHub.h"

namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.8f;
    static constexpr float ZoomOutFactor = 1.25f;

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
  {
    /* auto ltViewport = gf::RectF::fromPositionSize({ 0.0f, 0.0f }, { 0.5f, 1.0f });
    m_WorldView.setViewport(ltViewport);
    m_HudView.setViewport(ltViewport);
     */

    addView(m_WorldView);
    addView(m_HudView);

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

  /*   m_WorldEntities.addEntity(m_ltMap);
    m_WorldEntities.addEntity(m_ltHero);
    m_WorldEntities.addEntity(m_ltRoot);

    addHudEntity(m_light);
 */
    

   /*  m_cameraActions.close.addCloseControl();
    m_cameraActions.zoomIn.addScancodeKeyControl(gf::Scancode::Up);
    m_cameraActions.zoomOut.addScancodeKeyControl(gf::Scancode::Down);
 */
    m_WorldView.setCenter({ 0.0f, 0.0f });
    m_WorldView.setSize(ViewSize);
    m_WorldView.setInitialFramebufferSize(m_game.getRenderer().getSize());
    m_HudView.setInitialFramebufferSize(m_game.getRenderer().getSize());

    
  }

  void MainScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    // Handle interact
    
    // Handle camera
    
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
    m_map.render(target, states);
    m_HudEntities.render(target, states);
    renderHudEntities(target, states);
  }

}