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
            Continent();
            Continent(std::string name, std::vector<LandId> lands);
            std::string getName() const;
            std::vector<LandId> get_lands() const;

            void add_land(LandId land);

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
