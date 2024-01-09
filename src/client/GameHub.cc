#include "GameHub.h"


namespace fisk { 
    GameHub::GameHub() : GameManager("FISK", { "../data/" }), mainScene(*this) {
        pushScene(mainScene);
    }
} 