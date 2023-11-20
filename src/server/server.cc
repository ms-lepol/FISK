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
    
    for (;;) {
        // Accept a new connection ...
        gf::TcpSocket client = listener.accept();
        gf::Log::info("(SERVER) Accepting new connections\n");
        if (client) {
        // and handle the client...
            gf::Log::info("(SERVER) new connection on %s\n", client.getRemoteAddress().getHostname().c_str());

            char msg[MAX] = "Hello world"; 
            uint8_t bytes[MAX];
            memcpy(&bytes, msg, sizeof(char)*MAX);

            if (client.sendBytes(bytes) != gf::SocketStatus::Data) {
                // Handle error
                gf::Log::error("(SERVER) Error while sending Bytes\n");
                return;
            }
        }
    }
}

int main(){
    initServer();
    std::cout << gf::Log::Info;
    std::cerr << gf::Log::Error;
    return 0;
}