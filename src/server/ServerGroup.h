#ifndef FISK_SERVER_GROUP_H
#define FISK_SERVER_GROUP_H

#include <cstdint>
#include <vector>

#include <gf/Ref.h>
#include <gf/Packet.h>

#include "../common/NetworkProtocolData.h"

#include "ServerPlayer.h"

namespace fisk {

  class ServerGroup {
  public:
    virtual ~ServerGroup();

    void addPlayer(ServerPlayer& player);
    void removePlayer(ServerPlayer& player);

    std::vector<PlayerData> getPlayers();

    bool areAllPlayersReady();

    bool isEmpty() const {
        return m_players.empty();
    }

    int32_t getPlayersCount() {
        return static_cast<int32_t>(m_players.size());
    }

    template<typename T>
    void send(gf::Id id, const T& data) {
        gf::Packet packet;
        packet.is(data);

        for (ServerPlayer& player : m_players) {
            if (player.id == id) {
                player.socket.sendPacket(packet);
                return;
            }
        }
    }

    template<typename T>
    void broadcast(const T& data) {
        gf::Packet packet;
        packet.is(data);

        for (ServerPlayer& player : m_players) {
            player.socket.sendPacket(packet);
        }
    }

    void cloneTo(ServerGroup& group);

    private:
      std::vector<gf::Ref<ServerPlayer>> m_players;
  };

}

#endif // FISK_SERVER_GROUP_H
