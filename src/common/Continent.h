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

            template<typename S>
            void serialisation(S& sa) {
                sa | continent_id | name | lands;
            }
    };

    template<typename S>
    S& operator|(S& sa, Continent& continent) {
        continent.serialisation(sa);
        return sa;
    }
}
#endif /* ifndef FISK_CONTINENT_H */
