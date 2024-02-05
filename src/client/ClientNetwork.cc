#include "ClientNetwork.h"

#include <gf/Log.h>
#include <thread>
#include <csignal>
#include <cinttypes>

#include "../common/NetworkProtocol.h"
#include "../common/NetworkConstants.h"
#include "CardScene.h"
#include "GameHub.h"
namespace fisk {

    ClientNetwork::ClientNetwork(GameHub& game, std::string name)
        : m_connecting(false),
        m_model(nullptr),
        m_players(nullptr),
        m_lobbies(nullptr),
        m_game(game)
    {
        std::signal(SIGINT, &ClientNetwork::signalHandler);
        m_player_data.name = name;
        m_player_data.ready = false;
    }

    ClientNetwork::~ClientNetwork() {
        if(hasGameModel()) delete m_model;
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

    void ClientNetwork::setClientId(gf::Id id) {
        m_player_data.id = id;
    }

    gf::Id ClientNetwork::getClientId() const {
        return m_player_data.id;
    }

    bool ClientNetwork::isClientReady() const {
        return m_player_data.ready;
    }
 

  void ClientNetwork::update() {
    std::lock_guard<std::mutex> guard(m_mutex);
    gf::Packet packeta;

    while (queue.poll(packeta)) {
   
      switch (packeta.getType()) {
        case ServerHello::type: {
          gf::Log::info("(CLIENT) Hello.\n");
          auto data = packeta.as<ServerHello>();
          m_game.clientNetwork.setClientId(data.playerId);
          gf::Log::info("(CLIENT) My ID {%" PRIX64 "}", data.playerId);
          break;
        }
        case ServerStartGame::type: {
          gf::Log::info("(CLIENT) Starting game.\n");
          auto data = packeta.as<ServerStartGame>();
          m_game.popScene();
          m_game.pushScene(m_game.mainScene);
          
          break;
        }
        case ServerListLobbyPlayers::type: {
            gf::Log::info("(CLIENT) Lobby Player List\n");
            if(hasPlayerList()) {
                *m_players = packeta.as<ServerListLobbyPlayers>();
            } 
            else {
                m_players = new ServerListLobbyPlayers(packeta.as<ServerListLobbyPlayers>());
            }
            for(auto player : m_players->players){
                gf::Log::debug("(CLIENT)\t - %s\n", player.name.c_str());
            }
            break;
        }
        case ServerReady::type: {
            gf::Log::info("(CLIENT) Ready.\n");
            auto data = packeta.as<ServerReady>();
            m_player_data.ready = data.ready;
            break;
        }
        case ServerListLobbys::type: {
            gf::Log::info("(CLIENT) Lobby List.\n");
            if(hasLobbyList()) {
                *m_lobbies = packeta.as<ServerListLobbys>();
            } else {
                m_lobbies = new ServerListLobbys(packeta.as<ServerListLobbys>());
            }
            break;
        }
        case Game::type: {
            gf::Log::info("(CLIENT) Game Model.\n");
            if(hasGameModel()) {
                *m_model = packeta.as<Game>();
            } else {
                m_model = new Game(packeta.as<Game>());
            }
            break;
        }
                    
        default:
          gf::Log::error("(CLIENT) Unknown packet type: %lu\n", packeta.getType());
          break;
      }
    }
  }
 
    void ClientNetwork::signalHandler(int sig) {
        assert(sig == SIGINT);
        g_running = false;
    }

    std::atomic_bool ClientNetwork::g_running(true);

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

        while (g_running) {
            gf::Packet packet;

            switch (m_socket.recvPacket(packet)) {
                case gf::SocketStatus::Data:
                    gf::Log::info("(CLIENT) recv data\n");
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
        return static_cast<bool>(m_model);
    }

    bool ClientNetwork::hasLobbyList() const {
        return static_cast<bool>(m_lobbies);
    }

    bool ClientNetwork::hasPlayerList() const {
        return static_cast<bool>(m_players);
    }

    const Game& ClientNetwork::getGameModel() const {
        return *m_model;
    }

    const ServerListLobbys& ClientNetwork::getLobbyList() const {
        return *m_lobbies;
    }

    const ServerListLobbyPlayers& ClientNetwork::getPlayerList() const {
        return *m_players;
    }
}
