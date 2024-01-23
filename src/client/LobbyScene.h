#ifndef FISK_LOBBY_SCENE_H
#define FISK_LOBBY_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>


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

    // views

  gf::ExtendView m_WorldView;
  gf::ScreenView m_HudView;

  
  //rendering


  gf::TextureAtlas m_hudAtlas;

  // containers

  gf::EntityContainer m_WorldEntities;
  gf::EntityContainer m_HudEntities;

  // entities

  // widgets


  // actions

  gf::Action m_interact;

   gf::Vector2f mousePos;

};

}

#endif // FISK_LOBBY_SCENE_H