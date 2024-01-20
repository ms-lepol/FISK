#include <algorithm>
#include <cstdint>
#include <gf/Serialization.h>
#include <gf/SocketTypes.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include <gf/SocketSelector.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

#include "common/Card.h"
#include "common/Enums.h"
#include "common/NetworkConstants.h"

void initServer(){
    gf::TcpListener listener(fisk::PORT);
    gf::Log::info("(SERVER) Launching server on port %s\n", fisk::PORT);

    gf::SocketSelector selector;
    selector.addSocket(listener);

    std::vector<gf::TcpSocket> sockets;

    for (;;) {

        if(selector.wait() == gf::SocketSelectorStatus::Event){
            for(auto& socket : sockets){
                if(selector.isReady(socket)){
                    // Read data from the socket
                }
            }
        }

        // Accept a new connection ...
        if(selector.isReady(listener)){
            gf::TcpSocket client = listener.accept();
            gf::Log::info("(SERVER) Accepting new connections\n");
            sockets.push_back(std::move(client));
            selector.addSocket(sockets.back());
            if (client) {
            // and handle the client...
                gf::Log::info("(SERVER) new connection on %s\n", client.getRemoteAddress().getHostname().c_str());

                fisk::Card card(fisk::Type::Gunner, 0);

                std::vector<uint8_t> bytes(fisk::MAX);
                gf::BufferOutputStream buffered_stream(&bytes);
                gf::Serializer sa(buffered_stream);

                sa | card;

                if (client.sendBytes(bytes) != gf::SocketStatus::Data) {
                    // Handle error
                    gf::Log::error("(SERVER) Error while sending Bytes\n");
                    return;
                }
            }
        }
    }
    gf::Log::info("(SERVER) Server Closed");
}

int main(){
    initServer();
    return 0;
}
