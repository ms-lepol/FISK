#include <algorithm>
#include <cstdint>
#include <cstring>
#include <gf/TcpSocket.h>
#include <gf/Log.h>
#include <iostream>

#define HOSTNAME "127.0.0.1"
#define PORT "25000"
#define MAX 2048 


void initClient(){
    // Create a socket to example.com on port 24680
    gf::TcpSocket socket(HOSTNAME, PORT);
    gf::Log::info("(CLIENT) Trying to connect to %s\n", socket.getRemoteAddress().getHostname().c_str());

    if (!socket) {
        // Handle error
        gf::Log::error("(CLIENT) Error while connecting to the socket\n");
        return;
    }
    
    uint8_t bytes[MAX];
    
    if (socket.recvBytes(bytes) != gf::SocketStatus::Data) {
        // Handle error
        gf::Log::error("(CLIENT) Error while retrieving the socket\n");
        return;
    }

    char msg [MAX];
    memcpy(&msg, bytes, sizeof(uint8_t)*MAX);

    gf::Log::info("(CLIENT) Received : %s\n", msg);
}

int main(){
    initClient();
    std::cout << gf::Log::Info;
    std::cerr << gf::Log::Error;
    return 0;
}