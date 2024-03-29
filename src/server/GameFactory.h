#ifndef FISK_GAME_FACTORY_H
#define FISK_GAME_FACTORY_H

#include <memory>

#include "GameInstance.h"

namespace fisk {

  class GameFactory {
  public:
    virtual std::unique_ptr<GameInstance> createInstance(gf::Random& random) = 0;
  };

}

#endif // FISK_GAME_FACTORY_H
