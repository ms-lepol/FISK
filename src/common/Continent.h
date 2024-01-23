#ifndef FISK_CONTINENT_H
#define FISK_CONTINENT_H
#include "Constants.h"
#include <string>
#include <vector>

namespace fisk {

    class Continent {
        protected:
            std::string name;
            std::vector<LandId> lands;
        public:
            Continent(std::string name, std::vector<LandId> lands);
            std::string getName();

            template<typename S>
            void serialisation(S& sa) {
                sa | name | lands;
            }
    };

    template<typename S>
    S& operator|(S& sa, Continent& continent) {
        continent.serialisation(sa);
        return sa;
    }
}
#endif /* ifndef FISK_CONTINENT_H */
