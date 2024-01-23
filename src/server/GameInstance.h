#ifndef FISK_GAME_INSTANCE_H
#define FISK_GAME_INSTANCE_H

#include <gf/Ref.h>
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
            virtual void start() = 0;
            virtual bool isFinished() = 0;

    };

}

#endif // FISK_GAME_INSTANCE_H
