#include "ServerLobby.h"
#include "ServerPlayer.h"
#include "../common/NetworkProtocol.h"

#include <algorithm>
#include <cinttypes>

#include <gf/Log.h>

namespace fisk {

    ServerLobby::ServerLobby(GameFactory& factory)
    : m_factory(factory),
    m_instance(nullptr)
    {

    }

    void ServerLobby::update(ServerPlayer& player, gf::Packet& packet) {
        assert(player.lobby == this);

        switch (packet.getType()) {
        case ClientReady::type: {
            gf::Log::info("(LOBBY) {%" PRIX64 "} Ready.\n", player.id);
            if (isGameStarted()) {
                gf::Log::warning("(LOBBY) {%" PRIX64 "} Game already started\n", player.id);
                ServerError error;
                error.reason = ServerError::GameAlreadyStarted;
                player.send(error);
                break;
            }
            auto data = packet.as<ClientReady>();
            player.ready = data.ready;
            // send an acknowledgement to the player
            ServerReady ready;
            ready.ready = data.ready;
            player.send(ready);
            // broadcast new state
            broadcastPlayers();
            // Check if everyone is ready
            startGameIfReady();
            break;
        }
        }
    }

    void ServerLobby::broadcastPlayers() {
        ServerListLobbyPlayers data;
        data.players = getPlayers();
        broadcast(data);
    }

    bool ServerLobby::isGameStarted() {
        return m_instance != nullptr;
    }

    void ServerLobby::startGameIfReady() {
        if (!areAllPlayersReady()) {
            return;
        }
        ServerStartGame data;
        broadcast(data);

        m_instance = m_factory.get().createInstance();
        cloneTo(*m_instance);
        m_instance->start();
    }
}
