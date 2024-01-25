#include "GameInstance.h"
#include <algorithm>
#include <gf/Log.h>
#include <memory>

namespace fisk {

    GameInstance::GameInstance(std::unique_ptr<Game> model):
        model(std::move(*model)) {
    }

    void GameInstance::start() {
        gf::Log::info("GameInstance started");
    }

    bool GameInstance::isFinished() {
        return false;
    }
}
