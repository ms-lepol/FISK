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
#include "HudButtons.h"
#include "UnitSelector.h"

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
  void doProcessEvent(gf::Event& event) override;

private:
  GameHub& m_game;

    // views


  //rendering

  PlayerColor m_playerColor;
   gf::RectangleShape background;
  gf::TextureAtlas m_hudAtlas;

  // entities
  public:
  fisk::MapEntity m_map;
  private:
  fisk::TurnInterface m_turnInterface;
  fisk::PhaseIndicator m_phaseIndicator;
  

  // widgets

  fisk::HudButtons m_hudButtons;

  // actions

  CameraActions m_cameraActions;
  gf::Action m_interact;

   gf::Vector2f mousePos;

   public:
    fisk::UnitSelector m_unitSelector;
};

}

#endif // FISK_MAIN_SCENE_H