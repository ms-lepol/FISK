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
  , m_WorldView({ViewSize.x/2,ViewSize.y/2 }, ViewSize)
  , m_interact("Interact")
  , m_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  {
   
    // Views
    addView(m_WorldView);
    addView(m_HudView);
    
    //Rendering configuration
    m_HudView.setSize(ViewSize); 
    m_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

   

   
    //World entities
   
    //HUD entities

   
    std::cout << "hud size: " << m_HudView.getSize().x << " "<< m_HudView.getSize().y<<std::endl;
    
    

    // Interact Action
    m_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(m_interact);


    m_WorldView.setInitialFramebufferSize(m_game.getRenderer().getSize());
    //m_HudView.setSize(ViewSize);
    m_HudView.setInitialFramebufferSize(m_game.getRenderer().getSize());
  }

  void CardScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    
    // Handle interact
    if (m_interact.isActive()) {
    /*   
      m_hudButtons.widg_container.pointTo(mousePos);
      m_hudButtons.widg_container.triggerAction();
      
      m_map.widg_container.pointTo(mousePos);
      m_map.widg_container.triggerAction(); */

      m_interact.reset();
    }
  }

  void CardScene::doUpdate(gf::Time time) {
    gf::Event event;
    while (m_game.getWindow().pollEvent(event)){;
      if (event.type == gf::EventType::MouseMoved) {
        mousePos = event.mouseCursor.coords;
      }
    }

    m_WorldEntities.update(time);
    m_HudEntities.update(time);


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
    target.setView(m_WorldView);
    target.setView(m_HudView);

    m_WorldEntities.render(target, states);
    m_HudEntities.render(target, states);
    
    renderHudEntities(target, states);
  }

}