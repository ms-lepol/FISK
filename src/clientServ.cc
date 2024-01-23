#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <gf/Serialization.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/Log.h>
#include <gf/Sleep.h>
#include <iostream>
#include <vector>
#include <cinttypes>

#include "common/NetworkConstants.h"
#include "client/ClientNetwork.h"
#include "common/NetworkProtocol.h"


int main(){

    fisk::ClientNetwork clientNetwork;

    // Wait connection
    clientNetwork.connect(fisk::HOSTNAME);
    gf::sleep(gf::milliseconds(500));
    if(!clientNetwork.isConnected()){
      gf::Log::error("(CLIENT) Could not connect to the server.");
      return EXIT_FAILURE;
    }
    gf::Log::info("(CLIENT) Successfully connected to server.");

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
        gf::Log::debug("(CLIENT) Player ID : {%" PRIX64 "}", data.playerId);
    }

}
/*
    // Create a socket to HOSTNAME on port 25000
    gf::TcpSocket socket(fisk::HOSTNAME, fisk::PORT);
    gf::Log::info("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());
    printf("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());

    if (!socket) {
        // Handle error
        gf::Log::error("(CLIENT) Error while connecting to the socket\n");
        return;
    }
    
    fisk::Card card(fisk::Type::Infantery, 0);

    std::vector<uint8_t> bytes(fisk::MAX);
    gf::BufferInputStream buffer(&bytes);
    gf::Deserializer sa(buffer);

    if (socket.recvBytes(bytes) != gf::SocketStatus::Data) {
        // Handle error
        gf::Log::error("(CLIENT) Error while retrieving the socket\n");
        return;
    }

    sa | card;


    gf::Log::info("(CLIENT) Received : %hhu\n", card.getType());
}

int main(){
    initClient();
    return 0;
}
*/