#ifndef FISK_GAME_HUB_H
#define FISK_GAME_HUB_H

#include <gf/GameManager.h>

#include "CardScene.h"
#include "EndScene.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "LobbyScene.h"
#include "ClientNetwork.h"

namespace fisk {

  struct GameHub : gf::GameManager {
    GameHub(std::string client_name = "Michel");

    MainScene mainScene;
    CardScene cardScene;
    LobbyScene lobbyScene;
    TitleScene titleScene;
    EndScene endScene;

    ClientNetwork clientNetwork;    
  };

}


#endif // RC_GAME_HUB_H