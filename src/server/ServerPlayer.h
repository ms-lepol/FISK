#ifndef FISK_SERVER_PLAYER_H
#define FISK_SERVER_PLAYER_H

#include <cstdint>
#include <string>

#include <gf/Packet.h>
#include <gf/TcpSocket.h>

namespace fisk {

  class ServerLobby;

  struct ServerPlayer {
    gf::Id id = gf::InvalidId;
    std::string name;
    gf::TcpSocket socket;
    ServerLobby *lobby = nullptr;
    bool ready = false;

    template<typename T>
    void send(const T& data) {
      gf::Packet packet;
      packet.is(data);
      socket.sendPacket(packet);
    }
  };

}

#endif // FISK_SERVER_PLAYER_H
