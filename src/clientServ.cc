#include <algorithm>
#include <cstdint>
#include <cstring>
#include <gf/Serialization.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/Log.h>
#include <iostream>
#include <vector>

#include "common/NetworkConstants.h"
#include "common/Card.h"


void initClient(){
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
