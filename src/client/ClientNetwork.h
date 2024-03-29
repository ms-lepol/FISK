#ifndef FISK_CLIENT_NETWORK_H
#define FISK_CLIENT_NETWORK_H

#include "../common/NetworkConstants.h"
#include "../common/Game.h"
#include "../common/NetworkProtocol.h"


#include <atomic>
#include <gf/Id.h>
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
        ClientNetwork(GameHub& game, std::string name);
        ~ClientNetwork();

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

        bool hasLobbyList() const;
        bool hasPlayerList() const;
        bool hasGameModel() const;

        gf::Id getClientId() const;
        void setClientId(gf::Id id);

        bool isClientReady() const;

        const ServerListLobbys& getLobbyList() const;
        const ServerListLobbyPlayers& getPlayerList() const;
        const Game& getGameModel() const;
    
    public:
    gf::Queue<gf::Packet> queue;
    std::mutex m_mutex;
    void update();

    private:
    void run(std::string hostname);

    private:
        static void signalHandler(int sig);
        static std::atomic_bool g_running;

        GameHub& m_game;
        gf::TcpSocket m_socket;
        std::atomic_bool m_connecting;

        ServerListLobbys* m_lobbies;
        ServerListLobbyPlayers* m_players;
        Game* m_model;
        
        PlayerData m_player_data;
    };

}

#endif // FISK_CLIENT_NETWORK_H
