#include "GameHub.h"
#include <gf/Log.h>
#include <gf/Packet.h>
#include <gf/Sleep.h>
#include <gf/Time.h>

namespace fisk {

    constexpr gf::Vector2f ViewSize = { 1280.0f, 720.0f };

    GameHub::GameHub(std::string client_name) : GameManager("FISK", { "../data/" })
    , mainScene(*this)
    , cardScene(*this)
    , lobbyScene(*this)
    , titleScene(*this)
    , clientNetwork(*this, client_name)
    , endScene(*this) {

        clientNetwork.connect(HOSTNAME);

        while (!clientNetwork.isConnected()) {
            gf::sleep(gf::milliseconds(1));
        }
        {
            ClientHello hello;
            hello.name = client_name;
            clientNetwork.send(hello);
            gf::Packet packet;
            clientNetwork.queue.wait(packet);
            if(packet.getType() != ServerHello::type) {
                gf::Log::error("expected ServerHello got smth else\n");
            }
            clientNetwork.queue.wait(packet);
            if(packet.getType() != ServerListLobbys::type) {
                gf::Log::error("expected ServerListLobbys got smth else\n");
            }
            ServerListLobbys list = packet.as<ServerListLobbys>();
            if (list.lobbys.size() == 0) {
                ClientCreateLobby msg;
                msg.name = "Lobby des Michels";
                clientNetwork.send(msg);
            } else {
                ClientJoinLobby msg;
                msg.lobby = list.lobbys.front().id;
                clientNetwork.send(msg);
            }
        }
        cardScene.setWorldViewSize({720,480});
        cardScene.setWorldViewCenter({ViewSize.x/2,ViewSize.y/2});
        /* 
        mainScene.setWorldViewSize({ 1280, 720 });
        pushScene(mainScene);
        mainScene.pause(); */
        pushScene(lobbyScene);
    }
}
