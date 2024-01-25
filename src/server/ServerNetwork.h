#ifndef FISK_SERVER_NETWORK_H
#define FISK_SERVER_NETWORK_H

#include <atomic>
#include <gf/Id.h>
#include <map>

#include "../common/Constants.h"
#include "Map1Factory.h"
#include "ServerPlayer.h"
#include "ServerLobby.h"

#include <gf/Random.h>
#include <gf/Ref.h>
#include <gf/SocketSelector.h>
#include <gf/TcpListener.h>

namespace fisk {

  class ServerNetwork {
  public:
    ServerNetwork(gf::Random& random);

    void run();

    void update(ServerPlayer& player, gf::Packet& packet);

    std::vector<LobbyData> getLobbys();

    void joinLobby(ServerLobby& lobby);
    void createLobby();

    void broadcastLobbys();

    template<typename T>
    void send(gf::Id id, const T& data) {
        gf::Packet packet;
        packet.is(data);

        for (auto& key : m_players) {
            if (key.first == id) {
                key.second.socket.sendPacket(packet);
                return;
            }
        }
    }

    template<typename T>
    void broadcast(const T& data) {
        gf::Packet packet;
        packet.is(data);

        for (auto& key : m_players) {
            key.second.socket.sendPacket(packet);
        }
    }

  private:
    static void signalHandler(int sig);

  private:
    
    Map1Factory map_factory;

    gf::Ref<gf::Random> m_random;
    gf::TcpListener m_listener;
    gf::SocketSelector m_selector;

    std::map<gf::Id, ServerPlayer> m_players;
    std::map<gf::Id, ServerLobby> m_lobbys;

    static std::atomic_bool g_running;

  };

}

#endif // FISK_SERVER_NETWORK_H
