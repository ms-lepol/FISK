#ifndef FISK_CONTINENT_H
#define FISK_CONTINENT_H
#include "Constants.h"
#include <string>
#include <vector>

namespace fisk {

    class Continent {
        protected:
            ContinentId continent_id;
            std::string name;
            std::vector<unsigned> lands;
        public:
            Continent(std::string name, std::vector<LandId> lands);
            std::string getName();
        };
}
#endif /* ifndef FISK_CONTINENT_H */
