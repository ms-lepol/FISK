#include "ServerNetwork.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <gf/Serialization.h>
#include <gf/SocketTypes.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include <gf/SocketSelector.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <csignal>
#include <cinttypes>

#include "../common/NetworkConstants.h"
#include "../common/NetworkProtocol.h"
#include "GameFactory.h"
#include "Map1Factory.h"
#include "ServerPlayer.h"

namespace fisk {

    ServerNetwork::ServerNetwork(gf::Random& random) :
    m_listener(PORT),
    m_random(random)
    {
        if(!m_listener){
            throw std::runtime_error("(SERVER) Can not start listener.");
        }

        std::signal(SIGINT, &ServerNetwork::signalHandler);
        m_selector.addSocket(m_listener);

        gf::Log::info("(SERVER) Launching server on port %s\n", fisk::PORT);
    }

    void ServerNetwork::run(){
        static constexpr gf::Time Timeout = gf::seconds(1); // Wake up the server every seconds to see if something happened

        while (g_running) {
            auto status = m_selector.wait(Timeout);

            if (status == gf::SocketSelectorStatus::Timeout) {
                continue;
            }

            if (status == gf::SocketSelectorStatus::Error) {
                gf::Log::error("(SERVER) An error occurred in the selector. Stopping the server...\n");
                break;
            }

            std::vector<gf::Id> to_disconnect;

            for (auto& key : m_players) {
                auto& player = key.second;

                if (m_selector.isReady(player.socket)) {
                    gf::Packet packet;

                    switch (player.socket.recvPacket(packet)) {

                        case gf::SocketStatus::Data:
                            switch (packet.getType()) {
                                case ClientDisconnect::type:
                                    gf::Log::info("(SERVER) {%" PRIX64 "} Disconnected.\n", player.id);
                                    to_disconnect.push_back(player.id);
                                    break;
                                default:
                                    //gf::Log::debug("(SERVER) {%" PRIX64 "} Updating.\n", player.id);
                                    update(player, packet);
                                    if(player.lobby != nullptr) {
                                        player.lobby->update(player, packet);
                                    }
                                    break;
                            }
                            break;

                        case gf::SocketStatus::Error:
                            gf::Log::error("(SERVER) {%" PRIX64 "} Error receiving data.\n", player.id);
                            // fallthrough
                        case gf::SocketStatus::Close:
                            gf::Log::info("(SERVER) {%" PRIX64 "} Socket closed.\n", player.id);
                            to_disconnect.push_back(player.id);
                            break;
                        case gf::SocketStatus::Block:
                            assert(false);
                            break;
                    }
                }
            }

            // Accept new connection
            if (m_selector.isReady(m_listener)) {
                gf::TcpSocket socket = m_listener.accept();

                if (!socket) continue;

                gf::Id id = m_random.get().computeId(); // assume it's unique

                ServerPlayer playerInstance;
                playerInstance.id = id;
                playerInstance.name = ""; // no name yet
                playerInstance.socket = std::move(socket);

                auto res = m_players.emplace(id, std::move(playerInstance));
                assert(res.second);
                auto& player = res.first->second;
                m_selector.addSocket(player.socket);

                gf::Log::info("(SERVER) {%" PRIX64 "} Connected.\n", player.id);
            }

            if (!to_disconnect.empty()) {
                for (auto id : to_disconnect) {
                    auto it = m_players.find(id);
                    assert(it != m_players.end());
                    auto& player = it->second;
                    m_selector.removeSocket(player.socket);
                    m_players.erase(it);
                }
            }
        }
    }

    void ServerNetwork::signalHandler(int sig) {
        assert(sig == SIGINT);
        g_running = false;
    }

    std::atomic_bool ServerNetwork::g_running(true);

    void ServerNetwork::update(ServerPlayer& player, gf::Packet& packet) {
        switch (packet.getType()) {
            case ClientHello::type: {
                gf::Log::info("(SERVER) {%" PRIX64 "} Hello received.\n", player.id);
                auto data = packet.as<ClientHello>();
                player.name = data.name;
                // send an acknowledgement to the player
                ServerHello hello;
                hello.playerId = player.id;
                player.send(hello);
                // send list of lobbys
                ServerListLobbys list;
                list.lobbys = getLobbys();
                player.send(list);
                break;
            }

            case ClientCreateLobby::type: {
                gf::Log::info("(SERVER) {%" PRIX64 "} Create lobby.\n", player.id);
                if(player.lobby != nullptr) {
                    gf::Log::warning("(SERVER) PlayerAlreadyInLobby\n");
                    ServerError data;
                    data.reason = ServerError::PlayerAlreadyInLobby;
                    player.send(data);
                    break;
                }
                auto data = packet.as<ClientCreateLobby>();
                ServerLobby lobby(map_factory);
                lobby.id = m_random.get().computeId();
                lobby.name = data.name;

                lobby.addPlayer(player);

                auto res = m_lobbys.emplace(lobby.id, std::move(lobby));
                assert(res.second);
                player.lobby = &res.first->second;
                broadcastLobbys();
                break;
            }

            case ClientJoinLobby::type: {
                gf::Log::info("(SERVER) {%" PRIX64 "} Join lobby.\n", player.id);
                if(player.lobby != nullptr) {
                    gf::Log::warning("(SERVER) PlayerAlreadyInLobby\n");
                    ServerError data;
                    data.reason = ServerError::PlayerAlreadyInLobby;
                    player.send(data);
                    break;
                }
                ServerLobby& lobby = m_lobbys.find(packet.as<ClientJoinLobby>().lobby)->second;
                if(lobby.getPlayersCount() == 4){
                    gf::Log::warning("(SERVER) FullLobby\n");
                    ServerError data;
                    data.reason = ServerError::FullLobby;
                    player.send(data);
                    break;
                }
                lobby.addPlayer(player);
                player.lobby = &lobby;
                
                break;
            }

            case ClientLeaveLobby::type: {
                gf::Log::info("(SERVER) {%" PRIX64 "} Leave lobby.\n", player.id);
                if(player.lobby == nullptr) {
                    gf::Log::warning("(SERVER) PlayerNotInLobby\n");
                    ServerError data;
                    data.reason = ServerError::PlayerNotInLobby;
                    player.send(data);
                    break;
                }
                ServerLobby& lobby = m_lobbys.find(packet.as<ClientJoinLobby>().lobby)->second;
                lobby.removePlayer(player);
                if(lobby.isEmpty()){
                    m_lobbys.erase(packet.as<ClientJoinLobby>().lobby);
                }
                player.lobby = nullptr;
                broadcastLobbys();
                break;
            }

            //default:
                //gf::Log::debug("(SERVER) {%" PRIX64 "} Nothing to do.\n", player.id);
            
        }
    }

    std::vector<LobbyData> ServerNetwork::getLobbys() {
        std::vector<LobbyData> list;

        for (auto& kv : m_lobbys) {
            auto& lobby  = kv.second;
            LobbyData data;
            data.id = lobby.id;
            data.name = lobby.name;
            data.players = lobby.getPlayersCount();
            list.push_back(std::move(data));
        }

        return list;
    }

    void ServerNetwork::broadcastLobbys() {
        ServerListLobbys data;
        data.lobbys = getLobbys();
        broadcast(data);
    }

}
