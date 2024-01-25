#ifndef FISK_GAME_INSTANCE_H
#define FISK_GAME_INSTANCE_H

#include <gf/Ref.h>
#include <memory>
#include <vector>
#include "../common/NetworkProtocol.h"
#include "../common/NetworkProtocolData.h"
#include "../common/Game.h"
#include "ServerGroup.h"
#include "ServerPlayer.h"

namespace fisk {

    class GameInstance : public ServerGroup{

        Game model;

        public:

            GameInstance(std::unique_ptr<Game> model);

            void start();
            bool isFinished();

    };

}

#endif // FISK_GAME_INSTANCE_H
