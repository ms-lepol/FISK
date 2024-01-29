#include "ClientNetwork.h"

#include <gf/Log.h>
#include <thread>

#include "../common/NetworkProtocol.h"
#include "../common/NetworkConstants.h"

namespace fisk {

    ClientNetwork::ClientNetwork()
        : m_connecting(false),
        m_game(nullptr),
        m_players(nullptr),
        m_lobbies(nullptr)
    {}

    ClientNetwork::~ClientNetwork() {
        if(hasGameModel()) delete m_game;
        if(hasPlayerList()) delete m_players;
        if(hasLobbyList()) delete m_lobbies;
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
                    gf::Log::info("(CLIENT) recv data\n");
                    if(packet.getType() == ServerListLobbys::type) {
                        if(hasLobbyList()) {
                            *m_lobbies = packet.as<ServerListLobbys>();
                        } else {
                            m_lobbies = new ServerListLobbys(packet.as<ServerListLobbys>());
                        }
                    }
                    if(packet.getType() == ServerListLobbyPlayers::type) {
                        if(hasPlayerList()) {
                            *m_players = packet.as<ServerListLobbyPlayers>();
                        } else {
                            m_players = new ServerListLobbyPlayers(packet.as<ServerListLobbyPlayers>());
                        }
                    }
                    if(packet.getType() == Game::type) {
                        if(hasLobbyList()) {
                            *m_game = packet.as<Game>();
                        } else {
                            m_game = new Game(packet.as<Game>());
                        }
                    }
                    queue.push(std::move(packet));
                    break;
                case gf::SocketStatus::Error:
                    gf::Log::error("(CLIENT) Error while receiving a packet from server\n");
                    return;
                case gf::SocketStatus::Close:
                    gf::Log::info("(CLIENT) End of connection to the server\n");
                    return;
                case gf::SocketStatus::Block:
                    assert(false);
                    break;
            }
        }
    }

    bool ClientNetwork::hasGameModel() const {
        return static_cast<bool>(m_game);
    }

    bool ClientNetwork::hasLobbyList() const {
        return static_cast<bool>(m_lobbies);
    }

    bool ClientNetwork::hasPlayerList() const {
        return static_cast<bool>(m_players);
    }

    const Game& ClientNetwork::getGameModel() const {
        return *m_game;
    }

    const ServerListLobbys& ClientNetwork::getLobbyList() const {
        return *m_lobbies;
    }

    const ServerListLobbyPlayers& ClientNetwork::getPlayerList() const {
        return *m_players;
    }
}
