#include "CardScene.h"
#include "CardEntity.h"
#include "CardScene.h"

#include "GameHub.h"
#include "HandEntity.h"
#include "LandEntity.h"
#include <gf/Anchor.h>
#include <gf/Color.h>
#include <gf/Event.h>
#include <gf/Keyboard.h>
#include <gf/Log.h>
#include <gf/Mouse.h>
#include <gf/Rect.h>
#include <gf/Shapes.h>
#include <gf/Texture.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <gf/MouseValues.h>
#include <iostream>
#include "../common/FiskColors.h"
namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSizeCard = {720.0f, 480.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.9f;
    static constexpr float ZoomOutFactor = 1.1f;

  }


  CardScene::CardScene(GameHub& game)
  : gf::Scene(ViewSizeCard)
  , m_game(game)
  , c_interact("Interact")
  , c_close("Close")
  , c_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  , c_handEntity(HandEntity(game))
  , c_playCard("Play", game.resources.getFont("font/PixelSplitter-Bold.ttf"),30)
  , c_closeButton(game.resources.getTexture("sprites/fisk_ui.png"), c_hudAtlas.getTextureRect("redCross"),c_hudAtlas.getTextureRect("redCross"),c_hudAtlas.getTextureRect("redCross"))
  {
    //Rendering configuration
    c_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));
    gf::Vector2f screenSize = {1280.0f, 720.0f};
    gf::Vector2f screenCenter = screenSize / 2.0f;
    
    setClearColor(HUDColor().backgroundColor);

    background.setSize({720.0f, 480.0f});
    background.setAnchor(gf::Anchor::Center);
    background.setPosition(screenCenter);
    background.setColor(HUDColor().buttonColor);
    background.setRadius(10.0f);
   
    //World entities
   
    c_hand.addEntity(c_handEntity);

    c_handEntity.setPosition(screenCenter + gf::Vector2f({-c_handEntity.getDimensions().x/2.0f, -CARD_HEIGHT/2.0f}));
    //HUD entities


    c_close.addKeycodeKeyControl(gf::Keycode::Escape);
    c_close.addKeycodeKeyControl(gf::Keycode::Q);

    // Interact Action
    c_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(c_interact);
    addAction(c_close);


    // Construct the hud buttons
    c_hudButtons.addWidget(c_closeButton);
    c_closeButton.setPosition( screenCenter + gf::Vector2f(ViewSizeCard.x/2-64, -ViewSizeCard.y/2));
    c_closeButton.setCallback([this](){
      gf::Log::info("CloseButton clicked\n");
      m_game.popScene();
    });

    c_hudButtons.addWidget(c_playCard);
    c_playCard.setPosition( screenCenter + gf::Vector2f(0, ViewSizeCard.y/2-64));
    c_playCard.setRadius(20);
    c_playCard.setDefaultTextColor(HUDColor().buttonColor);
    c_playCard.setDefaultBackgroundColor(HUDColor().backgroundColor);
    c_playCard.setPadding(20);
    c_playCard.setAnchor(gf::Anchor::Center);
    c_playCard.setCallback([this](){
      gf::Log::info("PlayCard clicked\n");
    });
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
      c_hudButtons.pointTo(mousePos);
      c_hudButtons.triggerAction();

      //TODO: Add card play action
      
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
    m_game.clientNetwork.update(); 
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

    // Draw the background
    
    target.draw(background, states);


    c_hand.render(target, states);
    c_hudButtons.render(target, states);
    
  }

}