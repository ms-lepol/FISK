#include <cstdlib>
#include <gf/Sleep.h>
#include <iostream>

#include "client/GameHub.h"
#include "client/ClientNetwork.h"
#include "common/NetworkProtocol.h"
#include "common/NetworkConstants.h"

int main(int argc, char *argv[]) {
    if(argc == 2){
        fisk::GameHub hub(argv[1]);
        hub.getWindow().setSize({1280,720});
        hub.run();
    } else {
        fisk::GameHub hub;
        hub.getWindow().setSize({1280,720});
        hub.run();
    }
    return EXIT_SUCCESS;
}

