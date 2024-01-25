#ifndef FISK_TITLE_SCENE_H
#define FISK_TITLE_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Views.h>


namespace fisk {

  struct GameHub;


class TitleScene : public gf::Scene {
public:
  TitleScene(GameHub& game);

private:
  void doHandleActions(gf::Window& window) override;
  void doUpdate(gf::Time time) override;
  void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;
  void doProcessEvent(gf::Event& event) override;

private:
  GameHub& m_game;

  std::array<char, 256> m_hostnameBuffer;
  std::array<char, 256> m_nameBuffer;
  bool m_connectionAsked;


    // views

  //rendering


  // containers

  gf::EntityContainer m_HudEntities;

  // entities

  // widgets

  

  // actions


  gf::Action m_interact;

   gf::Vector2f mousePos;

};

}

#endif // FISK_TITLE_SCENE_H