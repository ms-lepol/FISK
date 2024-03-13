#include "MainScene.h" 

#include "GameHub.h"
#include "LandEntity.h"
#include "UnitSelector.h"
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
#include <mutex>
#include "../common/FiskColors.h"

#define IS_DEV 1

namespace fisk {

    namespace {
        constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
        constexpr int ViewRadius = 7;

        static constexpr float ZoomInFactor = 0.9f;
        static constexpr float ZoomOutFactor = 1.1f;
        static constexpr int backgroundThickness = 5;

    }

    CameraActions::CameraActions()
        : close("Close")
        , win("win")
    {
    }

  MainScene::MainScene(GameHub& game)
  : gf::Scene(game.getRenderer().getSize())
  , m_game(game)
  
  , m_interact("Interact")
  , m_map(MapEntity(game,1))
  
  , m_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",game.resources))
  , m_DiceAtlas(gf::TextureAtlas("../data/sprites/dices_atlas.xml",game.resources))
  , m_turnInterface(TurnInterface(0,game.resources,m_hudAtlas))
  , m_phaseIndicator(PhaseIndicator(gf::Color4f({0,1,0,0}),game,m_hudAtlas))
  , m_hudButtons(HudButtons(game.resources,m_hudAtlas,game))
  , m_dices(game.resources, m_DiceAtlas, game)
  , m_unitSelector(game)
  {
   
    // Views
    setWorldViewCenter({ViewSize.x / 2, ViewSize.y / 2});   
    setWorldViewSize(ViewSize); 
    

    //Rendering configuration

    
    
    background.setOutlineThickness(backgroundThickness);
    background.setSize({static_cast<float>(game.getWindow().getSize().x-backgroundThickness*2),static_cast<float>(game.getWindow().getSize().y-backgroundThickness*2)});
    background.setPosition({static_cast<float>(backgroundThickness), static_cast<float>(backgroundThickness)});
    background.setColor(gf::Color::Transparent);
   

  
    
   
    m_hudAtlas.setTexture(game.resources.getTexture("sprites/fisk_ui.png"));

    setClearColor(gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255));

    m_phaseIndicator.setColor(m_playerColor.Orange);


    //World entities
    addWorldEntity(m_map);
    addWorldEntity(m_dices);
    

    //HUD entities

   addHudEntity(m_turnInterface);
   addHudEntity(m_phaseIndicator);
   addHudEntity(m_hudButtons);
   addHudEntity(m_unitSelector);

    m_turnInterface.setPosition({static_cast<int>(m_game.getWindow().getSize().x)-m_turnInterface.width- backgroundThickness,static_cast<int>(m_game.getWindow().getSize().y)/2});
    m_phaseIndicator.setPosition({static_cast<int>(m_game.getWindow().getSize().x)/2-m_phaseIndicator.width/2,static_cast<int>(m_game.getWindow().getSize().y) - m_turnInterface.height-backgroundThickness-20});
    m_hudButtons.placeCardButton({static_cast<int>(m_game.getWindow().getSize().x)/2-m_phaseIndicator.width - m_hudButtons.size,static_cast<int>(m_game.getWindow().getSize().y)-m_hudButtons.size-backgroundThickness-10});
    m_hudButtons.placeEndPhaseButton({static_cast<int>(m_game.getWindow().getSize().x)/2+ m_phaseIndicator.width/2+20,static_cast<int>(m_game.getWindow().getSize().y)-backgroundThickness-50});
    m_unitSelector.setPosition({static_cast<int>(m_game.getWindow().getSize().x-m_unitSelector.getDimensions().x),static_cast<int>(m_game.getWindow().getSize().y-m_unitSelector.getDimensions().y)});


    // Camera Actions 
    m_cameraActions.close.addCloseControl();
    m_cameraActions.close.addKeycodeKeyControl(gf::Keycode::Escape);
    m_cameraActions.close.isActive();

    m_cameraActions.win.addKeycodeKeyControl(gf::Keycode::W);
    m_cameraActions.win.isActive();
   
    addAction(m_cameraActions.close);
    if (IS_DEV) addAction(m_cameraActions.win);
    

    // Interact Action
    m_interact.addMouseButtonControl(gf::MouseButton::Left);

    addAction(m_interact);
    setFramebufferSize(ViewSize);
  }

  void MainScene::doHandleActions([[maybe_unused]] gf::Window& window) {
    if (!isActive()) {
      return;
    }
    
    // Handle camera
    if (m_cameraActions.close.isActive()) {
      m_game.getWindow().close();
    }

    if (m_cameraActions.win.isActive()) {
      m_game.popScene();
      m_game.pushScene(m_game.endScene);
    }

    // Handle interact
    if (m_interact.isActive()) {

        m_hudButtons.widg_container.pointTo(mousePosScreen);
        m_hudButtons.widg_container.triggerAction();

        m_map.widg_container.pointTo(mousePos);
        m_map.widg_container.triggerAction();

        m_unitSelector.s_container.pointTo(mousePosScreen);
        m_unitSelector.s_container.triggerAction();

        m_interact.reset();
    }
  }

  void MainScene::doUpdate(gf::Time time) {
    gf::Event event;
    while (m_game.getWindow().pollEvent(event)){;
      
    }
    background.setSize({static_cast<float>(m_game.getWindow().getSize().x-backgroundThickness*2),static_cast<float>(m_game.getWindow().getSize().y-backgroundThickness*2)});
    m_game.clientNetwork.update(); 

    //Update the HUD to fit the window size
    m_turnInterface.setPosition({static_cast<int>(m_game.getWindow().getSize().x)-m_turnInterface.width- backgroundThickness,static_cast<int>(m_game.getWindow().getSize().y)/2});
    m_phaseIndicator.setPosition({static_cast<int>(m_game.getWindow().getSize().x)/2-m_phaseIndicator.width/2,static_cast<int>(m_game.getWindow().getSize().y) - m_turnInterface.height-backgroundThickness-20});
    m_hudButtons.placeCardButton({static_cast<int>(m_game.getWindow().getSize().x)/2-m_phaseIndicator.width - m_hudButtons.size,static_cast<int>(m_game.getWindow().getSize().y)-m_hudButtons.size-backgroundThickness-10});
    m_hudButtons.placeEndPhaseButton({static_cast<int>(m_game.getWindow().getSize().x)/2+ m_phaseIndicator.width/2+20,static_cast<int>(m_game.getWindow().getSize().y)-backgroundThickness-50});
    m_unitSelector.setPosition({static_cast<int>(m_game.getWindow().getSize().x-m_unitSelector.getDimensions().x),static_cast<int>(m_game.getWindow().getSize().y-m_unitSelector.getDimensions().y)});

    std::lock_guard guard(m_game.clientNetwork.m_mutex);


        //Update the turn interface
        if (m_game.clientNetwork.hasGameModel()){
            auto& l_model = m_game.clientNetwork.getGameModel();
            m_turnInterface.setTurnOrder(l_model.get_player(l_model.get_current_player()).getColor4f());
            if (m_game.clientNetwork.hasPlayerList()){
                auto& l_playerList = m_game.clientNetwork.getPlayerList();
                m_turnInterface.setNbPlayer(l_playerList.players.size());
            }
        }
    }


    void MainScene::doProcessEvent(gf::Event& event) {
        if (!isActive()) {
            return;
        }
        if (event.type == gf::EventType::MouseMoved) {
            mousePosScreen = event.mouseCursor.coords;
        }
    }

  

  void MainScene::doRender(gf::RenderTarget& target, const gf::RenderStates& states) {

    
    if (m_game.clientNetwork.hasGameModel()){
        auto& l_model = m_game.clientNetwork.getGameModel();
        
        background.setOutlineColor(l_model.get_player(m_game.clientNetwork.getClientId()).getColor4f());
        
    }
    
    target.draw(background, states);
   
    renderWorldEntities(target,states);
    mousePos = target.mapPixelToCoords(mousePosScreen, getWorldView());
    renderHudEntities(target, states);
  }

}
