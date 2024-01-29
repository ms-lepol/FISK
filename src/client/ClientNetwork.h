#ifndef FISK_CLIENT_NETWORK_H
#define FISK_CLIENT_NETWORK_H

#include "../common/NetworkConstants.h"
#include "../common/NetworkProtocol.h"


#include <atomic>
#include <mutex>
#include <string>

#include <gf/Packet.h>
#include <gf/Queue.h>
#include <gf/TcpSocket.h>
#include <gf/Sleep.h>
#include <gf/Log.h>


namespace fisk {

    struct GameHub;

    class ClientNetwork {
    public:
        ClientNetwork(GameHub& game);

        bool isConnecting();
        bool isConnected();
        void connect(const std::string& hostname);
        void disconnect();

        template<typename T>
        void send(const T& data) {
            gf::Packet packet;
            packet.is(data);
            m_socket.sendPacket(packet);
        }
    
    public:
    gf::Queue<gf::Packet> queue;
    void update();

    private:
    void run(std::string hostname);

    private:
        GameHub& m_game;
        gf::TcpSocket m_socket;
        std::mutex m_mutex;
        std::atomic_bool m_connecting;
    };

}

#endif // FISK_CLIENT_NETWORK_H