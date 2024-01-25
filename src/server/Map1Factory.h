#ifndef MAP1_FACTOTY_H
#define MAP1_FACTOTY_H value

#include "GameFactory.h"

namespace fisk {
    class Map1Factory: public GameFactory {
        
        public:
        
        Map1Factory();
        std::unique_ptr<GameInstance> createInstance();
    };
}

#endif /* ifndef MAP1_FACTOTY_H */
