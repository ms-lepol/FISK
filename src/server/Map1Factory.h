#include <gf/Random.h>
#include <gf/Ref.h>
#ifndef MAP1_FACTOTY_H
#define MAP1_FACTOTY_H value

#include "GameFactory.h"

namespace fisk {
    class Map1Factory: public GameFactory {
        
        public:
        
        Map1Factory();
        std::unique_ptr<GameInstance> createInstance(gf::Random& random);

    };
}

#endif /* ifndef MAP1_FACTOTY_H */
