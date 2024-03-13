#include "EndScene.h"


#include "GameHub.h"

#include <gf/Anchor.h>
#include <sys/socket.h>
#include "../common/FiskColors.h"
namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.9f;
    static constexpr float ZoomOutFactor = 1.1f;
    static constexpr gf::Vector2f screenSize = {1280.0f, 720.0f};
    static gf::Vector2f screenCenter = screenSize / 2.0f;

  }


  EndScene::EndScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  , e_interact("Interact")
  , e_close("Close")
  , e_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  , e_replayButton("Play", game.resources.getFont("font/PixelSplitter-Bold.ttf"),30)
  , e_closeButton(game.resources.getTexture("sprites/fisk_ui.png"), e_hudAtlas.getTextureRect("redCross"),e_hudAtlas.getTextureRect("redCross"),e_hudAtlas.getTextureRect("redCross"))
  {
    //Rendering configuration
    e_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));
    setClearColor(HUDColor().backgroundColor);

    background.setColor(HUDColor().buttonColor);
    background.setRadius(10.0f);

    //World entities
    e_endText.setFont(game.resources.getFont("font/PixelSplitter-Bold.ttf"));
    e_endText.setCharacterSize(30);
    e_endText.setString("XXX has won the game");
    e_endText.setAnchor(gf::Anchor::Center);

    e_endText.setPosition(m_game.getWindow().getSize()/2);
    //HUD entities


    e_close.addKeycodeKeyControl(gf::Keycode::Escape);
    e_close.addKeycodeKeyControl(gf::Keycode::Q);

    // Interact Action
    e_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(e_interact);
    addAction(e_close);


    // Construct the hud buttons
    e_closeButton.setPosition(screenSize - gf::Vector2f(50,50));
    e_closeButton.setCallback([this](){
      gf::Log::info("CloseButton clicked\n");
      m_game.popScene();
    });

  }


  void EndScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    
    // Handle interact
    if (e_close.isActive()) {
      m_game.popScene();
    }

    if (e_interact.isActive()) {
      e_hudButtons.pointTo(mousePos);
      e_hudButtons.triggerAction();
    
      e_interact.reset();
    }
  }

  void EndScene::doUpdate(gf::Time time) {
    gf::Event event;
    while (m_game.getWindow().pollEvent(event)){;
      if (event.type == gf::EventType::MouseMoved) {
        mousePos = event.mouseCursor.coords;
      }
    }

    
    m_game.clientNetwork.update(); 
  }

  void EndScene::doProcessEvent(gf::Event& event) {
    if (!isActive()) {
      return;
    }
    if (event.type == gf::EventType::MouseMoved) {
      mousePos = event.mouseCursor.coords;
    }
  }

  void EndScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {
    
    // Draw the background
    
    gf::Vector2f screenSize = m_game.getWindow().getSize();
     setWorldViewCenter(screenSize/2);
    
    background.setSize(screenSize);
    background.setPosition({0,0});

   
    
    target.draw(background, states);
    e_endText.setPosition(m_game.getWindow().getSize()/2);
    e_endText.draw(target, states);
    e_replayButton.draw(target, states);
    e_replayButton.setPosition(screenSize/2 + gf::Vector2f(0, 100));


    renderWorldEntities(target, states);
   
    
  }

}