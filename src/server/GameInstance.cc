#include "GameInstance.h"
#include <gf/Log.h>

namespace fisk {

    GameInstance::GameInstance(Game model):
        model(model) {
    }

    void GameInstance::start() {
        gf::Log::info("GameInstance started");
    }

    bool GameInstance::isFinished() {
        return false;
    }
}
