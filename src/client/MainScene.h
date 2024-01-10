#ifndef FISK_MAIN_SCENE_H
#define FISK_MAIN_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Views.h>

#include "MapEntity.h"

namespace fisk {

  struct GameHub;

  struct CameraActions {
    CameraActions();
    
    gf::Action close;
    gf::Action zoomIn;
    gf::Action zoomOut;
  };



class MainScene : public gf::Scene {
public:
  MainScene(GameHub& game);

private:
  void doHandleActions(gf::Window& window) override;
  void doUpdate(gf::Time time) override;
  void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;

private:
  GameHub& m_game;

    // views

  gf::ExtendView m_WorldView;
  gf::ScreenView m_HudView;

  gf::ZoomingViewAdaptor adaptor;
  CameraActions m_cameraActions;

  // containers

  gf::EntityContainer m_WorldEntities;
  gf::EntityContainer m_HudEntities;

  // entities

  fisk::MapEntity m_map;
  // actions

};

}

#endif // FISK_MAIN_SCENE_H