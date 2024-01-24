#include <cstdlib>
#include <gf/Sleep.h>

#include "client/GameHub.h"
#include "client/ClientNetwork.h"
#include "common/NetworkProtocol.h"
#include "common/NetworkConstants.h"

int main(int argc, char *argv[]) {

    fisk::GameHub hub;
    hub.getWindow().setSize({1280,720});
    hub.run();
    return EXIT_SUCCESS;
}

