#ifndef FISK_GAME_HUB_H
#define FISK_GAME_HUB_H

#include <gf/GameManager.h>
#include "MainScene.h"

namespace fisk {

  struct GameHub : gf::GameManager {
    GameHub();

    MainScene mainScene;
  };

}


#endif // RC_GAME_HUB_H