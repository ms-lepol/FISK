#include <cstdlib>

#include "GameHub.h"

int main() {
  fisk::GameHub hub;
  hub.getWindow().setSize({1280,720});
  hub.run();

  return EXIT_SUCCESS;
}