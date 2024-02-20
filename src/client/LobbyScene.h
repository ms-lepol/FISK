#ifndef FISK_LOBBY_SCENE_H
#define FISK_LOBBY_SCENE_H

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Sprite.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include "../common/FiskColors.h"

#include "LobbyPlayer.h"


namespace fisk {

  struct GameHub;

  class TitleEntity : public gf::Entity {
    gf::Sprite sprite;
    gf::Texture& texture;
    gf::Vector2i direction;

  public:
    TitleEntity(gf::Texture& texture);
    void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
    void update(gf::Time time) override;
  };

  struct LobbyButton : public gf::Entity {
    gf::TextButtonWidget l_lobbyButton;
    gf::WidgetContainer l_hudButtons;
    LobbyButton(gf::Font* font) : l_lobbyButton("Ready", *font,30) {
      l_hudButtons.addWidget(l_lobbyButton);
    }

    void render(gf::RenderTarget& target, const gf::RenderStates& states) override {
      l_hudButtons.render(target, states);
    }

  };


class LobbyScene : public gf::Scene {
public:
  LobbyScene(GameHub& game);
  void addPlayer(gf::Id id, std::string name);
  void removePlayer(gf::Id id);
  void setPlayerReady(gf::Id id, bool isReady);
  void setPlayerPlot(gf::Id id, bool plotIsFilled);
  void setPlayerName(gf::Id id, std::string name);
  void resetPlayers();

private:
  void doHandleActions(gf::Window& window) override;
  void doUpdate(gf::Time time) override;
  void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;
  void doProcessEvent(gf::Event& event) override;

  
private:
  GameHub& m_game;

  //rendering
  gf::ExtendView l_hudView;
 
  gf::TextureAtlas l_hudAtlas;

  // containers

  

  // entities

  gf::Entity l_hudBackground;
  TitleEntity l_title;
  LobbyPlayer l_player1;
  LobbyPlayer l_player2;
  LobbyPlayer l_player3;
  LobbyPlayer l_player4;
  


  // widgets
  
  LobbyButton l_lobbyButton;

  // actions

  gf::Action l_interact;
  gf::Action l_close;

   gf::Vector2f mousePos;
    gf::Vector2i mousePosScreen;
};

}

#endif // FISK_LOBBY_SCENE_H
