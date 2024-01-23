#ifndef FISK_SERVER_LOBBY_H
#define FISK_SERVER_LOBBY_H

#include "ServerGroup.h"
#include "ServerPlayer.h"
#include "GameInstance.h"
#include "GameFactory.h"
#include "../common/NetworkProtocol.h"
#include <gf/Ref.h>

namespace fisk {

    class ServerLobby : public ServerGroup{
        public:
        ServerLobby(GameFactory& factory);

        void update(ServerPlayer& player, gf::Packet& packet);

        bool isGameStarted();

        void broadcastPlayers();

    private:
        void startGameIfReady();

    public:
        gf::Id id;
        std::string name;

    private:
        gf::Ref<GameFactory> m_factory;
        std::unique_ptr<GameInstance> m_instance;
    };

}

#endif // FISK_SERVER_LOBBY_H