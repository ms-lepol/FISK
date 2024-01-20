#include "ClientNetwork.h"

#include <gf/Log.h>
#include <thread>

#include "../common/NetworkProtocol.h"
#include "../common/NetworkConstants.h"

namespace fisk {

  ClientNetwork::ClientNetwork()
  : m_connecting(false)
  {

  }

  bool ClientNetwork::isConnecting() {
    return m_connecting;
  }

  bool ClientNetwork::isConnected() {
    std::lock_guard<std::mutex> guard(m_mutex);
    return static_cast<bool>(m_socket);
  }

  void ClientNetwork::connect(const std::string& hostname) {
    m_connecting = true;

    std::thread thread(&ClientNetwork::run, this, hostname);
    thread.detach();

  }

  void ClientNetwork::disconnect() {
    ClientDisconnect data;
    send(data);
    m_socket = gf::TcpSocket();
    m_connecting = false;
  }

  void ClientNetwork::run(std::string hostname) {
    gf::TcpSocket socket(hostname, PORT);
    gf::Log::info("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());

    if (!socket) {
      m_connecting = false;
      gf::Log::error("(CLIENT) Error while connecting to the socket\n");
      return;
    }

    {
      std::lock_guard<std::mutex> guard(m_mutex);
      m_socket = std::move(socket);
    }

    for (;;) {
      gf::Packet packet;

      switch (m_socket.recvPacket(packet)) {
        case gf::SocketStatus::Data:
          queue.push(std::move(packet));
          break;
        case gf::SocketStatus::Error:
          gf::Log::error("Error while receiving a packet from server\n");
          return;
        case gf::SocketStatus::Close:
          gf::Log::info("End of connection to the server\n");
          return;
        case gf::SocketStatus::Block:
          assert(false);
          break;
      }
    }
  }

}