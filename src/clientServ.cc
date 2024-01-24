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
