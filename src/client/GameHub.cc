#include "GameHub.h"


namespace fisk { 
    GameHub::GameHub() : GameManager("FISK", { "../data/" }), mainScene(*this) {
        mainScene.setWorldViewSize({ 1280, 720 });
        pushScene(mainScene);
    }
} 