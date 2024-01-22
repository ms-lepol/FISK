#ifndef FISK_CLIENT_NETWORK_H
#define FISK_CLIENT_NETWORK_H

#include <atomic>
#include <mutex>
#include <string>

#include <gf/Packet.h>
#include <gf/Queue.h>
#include <gf/TcpSocket.h>

namespace fisk {

    class ClientNetwork {
    public:
        ClientNetwork();

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

    private:
    void run(std::string hostname);

    private:
        gf::TcpSocket m_socket;
        std::mutex m_mutex;
        std::atomic_bool m_connecting;
    };

}

#endif // FISK_CLIENT_NETWORK_H