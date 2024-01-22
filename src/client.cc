#include <cstdlib>
#include <gf/Sleep.h>

#include "client/GameHub.h"
#include "client/ClientNetwork.h"
#include "common/NetworkProtocol.h"
#include "common/NetworkConstants.h"

int main(int argc, char *argv[]) {
    fisk::ClientNetwork clientNetwork;

    fisk::GameHub hub;
    hub.getWindow().setSize({1280,720});
    hub.run();

    // Wait connection
    clientNetwork.connect(fisk::HOSTNAME);
    gf::sleep(gf::milliseconds(500));
    assert(clientNetwork.isConnected());

    // Send hello package
    {
        fisk::ClientHello data;
        std::string name("Hello");
        assert(!name.empty());
        data.name = name;
        clientNetwork.send(data);
    }

    // Receive ack
    {
        gf::Packet packet;
        clientNetwork.queue.wait(packet);
        assert(packet.getType() == fisk::ServerHello::type);

        auto data = packet.as<fisk::ServerHello>();
        gf::Log::debug("Player ID : %lu", data.playerId);
    }

    return EXIT_SUCCESS;
}

/*

void initClient(){
    // Create a socket to HOSTNAME on port 25000
    gf::TcpSocket socket(HOSTNAME, PORT);
    gf::Log::info("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());
    printf("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());

    if (!socket) {
        // Handle error
        gf::Log::error("(CLIENT) Error while connecting to the socket\n");
        return;
    }
    
    fisk::Card card(fisk::Type::Infantery, 0);

    std::vector<uint8_t> bytes(MAX);
    gf::BufferInputStream buffer(&bytes);
    gf::Deserializer sa(buffer);

    if (socket.recvBytes(bytes) != gf::SocketStatus::Data) {
        // Handle error
        gf::Log::error("(CLIENT) Error while retrieving the socket\n");
        return;
    }

    sa | card;


    gf::Log::info("(CLIENT) Received : %d\n", card.getType());
}

int main(){
    initClient();
    return 0;
}

*/