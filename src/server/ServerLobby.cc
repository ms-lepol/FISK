#include "ServerLobby.h"
#include "ServerGroup.h"
#include "ServerPlayer.h"
#include "../common/NetworkProtocol.h"

#include <algorithm>
#include <cinttypes>

#include <gf/Log.h>

namespace fisk {

    ServerLobby::ServerLobby(GameFactory& factory, gf::Random& random)
    : m_factory(factory),
    m_instance(nullptr),
    m_random(random)
    {
        gf::Log::info("(LOBBY) Lobby Created.\n");
    }

    void ServerLobby::addPlayer(ServerPlayer& player) {
        ServerGroup::addPlayer(player);
        gf::Log::info("(LOBBY) {%" PRIX64 "} Added Client to Lobby.\n", player.id);
        broadcastPlayers();
    }

    void ServerLobby::removePlayer(ServerPlayer& player) {
        ServerGroup::removePlayer(player);
        gf::Log::info("(LOBBY) {%" PRIX64 "} Removed Client from Lobby.\n", player.id);
        m_instance->removePlayer(player);
        broadcastPlayers();
    }

    void ServerLobby::update(ServerPlayer& player, gf::Packet& packet) {
        assert(player.lobby == this);

        switch (packet.getType()) {
            case ClientReady::type: {
                gf::Log::info("(LOBBY) {%" PRIX64 "} Ready.\n", player.id);
                if (isGameStarted()) {
                    gf::Log::warning("(LOBBY) Game has already started.\n");
                    ServerError error;
                    error.reason = ServerError::GameAlreadyStarted;
                    player.send(error);
                    break;
                }
                auto data = packet.as<ClientReady>();
                player.ready = data.ready;
                // send an acknowledgement to the player
                ServerReady ack;
                ack.ready = data.ready;
                player.send(ack);
                // broadcast new state
                broadcastPlayers();
                // Check if everyone is ready
                startGameIfReady();
                break;
            }
        }
        if(isGameStarted()) {
            m_instance->update(player, packet);
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

        m_instance = m_factory.get().createInstance(m_random);
        cloneTo(*m_instance);
        m_instance->start();
    }
}
