#include <cstdlib>

#include "server/ServerNetwork.h"

int main(){
    fisk::ServerNetwork serverNetwork;
    serverNetwork.run();
    return EXIT_SUCCESS;
}
