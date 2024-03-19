#ifndef FISK_GAME_INSTANCE_H
#define FISK_GAME_INSTANCE_H

#include <gf/Id.h>
#include <gf/Packet.h>
#include <gf/Ref.h>
#include <map>
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
        bool ready;

        /**
         * ServerPlayer Id is the key
         * PlayerId is the model id 
         */
        std::map<gf::Id, PlayerId> srv_to_model_id;

        gf::Ref<gf::Random> m_random;

        public:

            GameInstance(std::unique_ptr<Game> model, gf::Random& random);

            void start();
            void update(ServerPlayer& player, gf::Packet& packet);
            bool isFinished();
            void removePlayer(ServerPlayer& player) override;

    };

}

#endif // FISK_GAME_INSTANCE_H
