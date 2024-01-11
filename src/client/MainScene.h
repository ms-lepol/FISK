#ifndef FISK_MAIN_SCENE_H
#define FISK_MAIN_SCENE_H

#include <gf/Scene.h>
#include <gf/Action.h>

#include <gf/RenderWindow.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>

#include "MapEntity.h"
#include "TurnInterface.h"
#include "PhaseIndicator.h"

namespace fisk {

  struct GameHub;

    struct PlayerColor {
      PlayerColor();
      gf::Color4f Blue;
      gf::Color4f Orange;
      gf::Color4f Green;
      gf::Color4f Yellow;
    };

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
  PlayerColor m_playerColor;

  gf::TextureAtlas m_hudAtlas;

  // containers

  gf::EntityContainer m_WorldEntities;
  gf::EntityContainer m_HudEntities;

  // entities

  fisk::MapEntity m_map;
  fisk::TurnInterface m_turnInterface;
  fisk::PhaseIndicator m_phaseIndicator;
  // actions

};

}

#endif // FISK_MAIN_SCENE_H