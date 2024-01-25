#include "CardScene.h"
#include "CardScene.h"

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

#include "FiskColors.h"

namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSize = {720.0f, 480.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.9f;
    static constexpr float ZoomOutFactor = 1.1f;

  }


  CardScene::CardScene(GameHub& game)
  : gf::Scene(ViewSize)
  , m_game(game)
  , c_interact("Interact")
  , c_close("Close")
  , c_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  {
    //Rendering configuration
    c_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(HUDColor().buttonColor);

   

   
    //World entities
   
    //HUD entities


    c_close.addKeycodeKeyControl(gf::Keycode::Escape);
    c_close.addKeycodeKeyControl(gf::Keycode::Q);

    // Interact Action
    c_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(c_interact);
    addAction(c_close);

  }

  void CardScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    
    // Handle interact
    if (c_close.isActive()) {
      m_game.popScene();
    }

    if (c_interact.isActive()) {

      c_interact.reset();
    }
  }

  void CardScene::doUpdate(gf::Time time) {
    gf::Event event;
    while (m_game.getWindow().pollEvent(event)){;
      if (event.type == gf::EventType::MouseMoved) {
        mousePos = event.mouseCursor.coords;
      }
    }

    c_hand.update(time);

  }

  void CardScene::doProcessEvent(gf::Event& event) {
    if (!isActive()) {
      return;
    }
    if (event.type == gf::EventType::MouseMoved) {
      mousePos = event.mouseCursor.coords;
    }
  }

  void CardScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {
    c_hand.render(target, states);
    c_hudButtons.render(target, states);
    
  }

}