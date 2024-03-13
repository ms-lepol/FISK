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
#include <sys/socket.h>
#include <vector>
#include "../common/FiskColors.h"
namespace fisk {

  namespace {
    constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
    constexpr int ViewRadius = 7;

    static constexpr float ZoomInFactor = 0.9f;
    static constexpr float ZoomOutFactor = 1.1f;
    static constexpr gf::Vector2f screenSize = {1280.0f, 720.0f};
    static gf::Vector2f ViewSizeCard = screenSize * 3.0f/4.0f;
    static gf::Vector2f screenCenter = screenSize / 2.0f;

  }


  CardScene::CardScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
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
    
    setClearColor(HUDColor().backgroundColor);

     setWorldViewCenter({ViewSize.x / 2, ViewSize.y / 2});   
    setWorldViewSize(ViewSize); 

    background.setSize(ViewSizeCard);
    background.setAnchor(gf::Anchor::Center);
    background.setPosition(screenCenter);
    background.setColor(HUDColor().buttonColor);
    background.setRadius(10.0f);
   
    //World entities
   
    addWorldEntity(c_handEntity);

    c_handEntity.setPosition(screenCenter + gf::Vector2f({-c_handEntity.getDimensions().x/2.0f, -CARD_HEIGHT/2.0f}));
    //HUD entities


    c_close.addKeycodeKeyControl(gf::Keycode::Escape);
    c_close.addKeycodeKeyControl(gf::Keycode::Q);

    // Interact Action
    c_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(c_interact);
    addAction(c_close);


    // Construct the hud buttons
    c_hudEntity.c_hudButtons.addWidget(c_closeButton);
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
    addWorldEntity(c_hudEntity);

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

      gf::Log::debug("(CARD SCENE) Interacting with cards\n");

      auto& mdl = m_game.clientNetwork.getGameModel();
      auto& curr_plyr = mdl.get_player(mdl.get_current_player());

      if(mdl.get_current_phase() != TurnPhase::Fortify || mdl.get_current_player() == m_game.clientNetwork.getClientId()) {
        c_interact.reset();
        return;
      }
      
      auto hand = mdl.get_player(mdl.get_current_player()).getHand();
      ClientGameSendCardsToPlay cards;
      bool can_send = false;
      if(hand.size() >= 3){ 
        std::vector<CardId> infantery;
        std::vector<CardId> gunner;
        std::vector<CardId> cavalry;
        std::vector<CardId> joker;

        for(CardId card : hand){
          switch(mdl.get_card(hand[card]).getType()){
            case Type::Infantery:
              infantery.push_back(card);
              break;
            case Type::Cavalry:
              cavalry.push_back(card);
              break;
            case Type::Gunner:
              gunner.push_back(card);
            case Type::Joker:
              joker.push_back(card);
              break;
          }
        }

        bool three_types_plus_joker = infantery.size() >= 1 && cavalry.size() >= 1 && gunner.size() >= 1
                                      ||infantery.size() >= 1 && cavalry.size() >= 1 && joker.size() >= 1
                                      ||infantery.size() >= 1 && joker.size() >= 1 && gunner.size() >= 1
                                      ||joker.size() >= 1 && cavalry.size() >= 1 && gunner.size() >= 1;

        // Case of three different card types (and cases with one joker)
        if(three_types_plus_joker){
          can_send = true;
          if(!infantery.empty()) cards.card_a = infantery[0];
          else cards.card_a = joker[0];
          if(!cavalry.empty()) cards.card_b = cavalry[0];
          else cards.card_b = joker[0];
          if(!gunner.empty()) cards.card_c = gunner[0];
          else cards.card_c = joker[0]; 
        }
        // TODO Still needs cases with 2 jokers
        else{
          if(infantery.size() >= 3) { // 3 infantery
            cards.card_a = infantery[0];
            cards.card_b = infantery[1];
            cards.card_c = infantery[2];
            can_send = true;
          } 
          else if(gunner.size() >= 3) { // 3 gunners
            cards.card_a = gunner[0];
            cards.card_b = gunner[1];
            cards.card_c = gunner[2];
            can_send = true;
          }
          else if(cavalry.size() >= 3) { // 3 cavalry
            cards.card_a = cavalry[0];
            cards.card_b = cavalry[1];
            cards.card_c = cavalry[2];
            can_send = true;
          }
          else if(joker.size() >= 3) { // 3 jokers
            cards.card_a = joker[0];
            cards.card_b = joker[1];
            cards.card_c = joker[2];
            can_send = true;
          }
        }
      }
      if(can_send) m_game.clientNetwork.send(cards);

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
    background.setSize(screenSize*(3.0f/4.0f));

    
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
    gf::Vector2f screenSize = m_game.getWindow().getSize();
    screenCenter = screenSize / 2.0f;
    ViewSizeCard = screenSize * 3.0f/4.0f;
    background.setSize(ViewSizeCard);
    background.setAnchor(gf::Anchor::Center);
    background.setPosition(screenCenter);
    
    target.draw(background, states);


    renderWorldEntities(target, states);
   
    
  }

}