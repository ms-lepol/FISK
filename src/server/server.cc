#include <gf/TcpSocket.h>
#include <gf/TcpListener.h>
#include <gf/Log.h>
#include <iostream>
#include <string.h>
#include <string>

#define PORT "25000"
#define MAX 2048 

void initServer(){
    gf::TcpListener listener(PORT);
    gf::Log::info("(SERVER) Launching server on port %s\n", PORT);
    printf("(SERVER) Launching server on port %s\n", PORT);
    
    for (;;) {
        // Accept a new connection ...
        gf::TcpSocket client = listener.accept();
        gf::Log::info("(SERVER) Accepting new connections\n");
        printf("(SERVER) Accepting new connections\n");
        if (client) {
        // and handle the client...
            gf::Log::info("(SERVER) new connection on %s\n", client.getRemoteAddress().getHostname().c_str());
            printf("(SERVER) new connection on %s\n", client.getRemoteAddress().getHostname().c_str());

            std::string name("Hello World!");

            const uint8_t * p = reinterpret_cast<const uint8_t*>(name.c_str());

            uint8_t bytes[MAX] = { 0x42, 0x69, 0x13, 0x12 };
    
            if (client.sendBytes(bytes) != gf::SocketStatus::Data) {
                // Handle error
                gf::Log::error("(SERVER) Error while sending Bytes\n");
                fprintf(stderr, "(SERVER) Error while sending Bytes\n");
                return;
            }

            gf::Log::info("(SERVER) sent %s\n", bytes);
            printf("(SERVER) sent %s\n", bytes);
        }
    }
}

int main(){
    initServer();
    return 0;
}