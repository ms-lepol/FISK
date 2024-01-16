#include <cstdint>
#include <gf/Serialization.h>
#include <gf/Streams.h>
#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include "../common/Card.h"
#include "../common/Enums.h"

#define PORT "25000"
#define MAX 2048

void initServer(){
    gf::TcpListener listener(PORT);
    gf::Log::info("(SERVER) Launching server on port %s\n", PORT);
    printf("(SERVER) Launching server on port %s\n", PORT);

    for (;;) {
        // Accept a new connection ...
        gf::TcpSocket socket = listener.accept();
        gf::Log::info("(SERVER) Accepting new connections\n");
        printf("(SERVER) Accepting new connections\n");
        if (socket) {
        // and handle the client...
            gf::Log::info("(SERVER) new connection on %s\n", socket.getRemoteAddress().getHostname().c_str());
            printf("(SERVER) new connection on %s\n", socket.getRemoteAddress().getHostname().c_str());

            fisk::Card card(fisk::Type::Gunner, 0);

            std::vector<uint8_t> bytes(MAX);
            gf::BufferOutputStream buffered_stream(&bytes);
            gf::Serializer sa(buffered_stream);

            sa | card;

            if (socket.sendBytes(bytes) != gf::SocketStatus::Data) {
                // Handle error
                gf::Log::error("(SERVER) Error while sending Bytes\n");
                fprintf(stderr, "(SERVER) Error while sending Bytes\n");
                return;
            }
        }
    }
}

int main(){
    initServer();
    return 0;
}
