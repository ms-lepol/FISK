#include "GameHub.h"


namespace fisk { 
    GameHub::GameHub() : GameManager("FISK", { "../data/" })
    , mainScene(*this) 
    , cardScene(*this) 
    , lobbyScene(*this) 
    , titleScene(*this) {

        

        mainScene.setWorldViewSize({ 1280, 720 });
        pushScene(mainScene);
        mainScene.pause();
        pushScene(lobbyScene);
    }
} 
