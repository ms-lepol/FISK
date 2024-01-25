#ifndef FISK_LOBBY_SCENE_H
#define FISK_LOBBY_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>


namespace fisk {

  struct GameHub;


class LobbyScene : public gf::Scene {
public:
  LobbyScene(GameHub& game);

private:
  void doHandleActions(gf::Window& window) override;
  void doUpdate(gf::Time time) override;
  void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;
  void doProcessEvent(gf::Event& event) override;

private:
  GameHub& m_game;

  //rendering
  gf::TextureAtlas l_hudAtlas;

  // containers

  gf::EntityContainer l_WorldEntities;
  gf::EntityContainer l_HudEntities;

  // entities

  


  // widgets
  gf::TextButtonWidget l_lobbyButton;
  gf::WidgetContainer l_hudButtons;


  // actions

  gf::Action l_interact;

   gf::Vector2f mousePos;

};

}

#endif // FISK_LOBBY_SCENE_H
