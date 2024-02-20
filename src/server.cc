#include <cstdlib>
#include <gf/Random.h>

#include "server/ServerNetwork.h"

int main(){
    gf::Random random(time(NULL));
    fisk::ServerNetwork serverNetwork(random);
    serverNetwork.run();
    return EXIT_SUCCESS;
}
