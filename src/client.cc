#include <cstdlib>

#include "client/GameHub.h"
#include "client/ClientNetwork.h"

int main() {
  fisk::ClientNetwork clientNetwork;

  fisk::GameHub hub;
  hub.getWindow().setSize({1280,720});
  hub.run();

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