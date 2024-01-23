#ifndef FISK_GAME_HUB_H
#define FISK_GAME_HUB_H

#include <gf/GameManager.h>
#include "ClientNetwork.h"
#include "CardScene.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "LobbyScene.h"

namespace fisk {

  struct GameHub : gf::GameManager {
    GameHub();

    MainScene mainScene;
    CardScene cardScene;
    LobbyScene lobbyScene;
    TitleScene titleScene;

    ClientNetwork clientNetwork;
    
  };

}


#endif // RC_GAME_HUB_H