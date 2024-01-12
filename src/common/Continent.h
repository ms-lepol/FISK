#ifndef FISK_CONTINENT_H
#define FISK_CONTINENT_H
#include <string>
#include <vector>

namespace fisk {

    class Continent {
        protected:
            unsigned Continent_id;
            std::string name;
            std::vector<unsigned> lands;
        public:
            Continent(std::string name, std::vector<unsigned> lands);
            std::string getName();
        };
}
#endif /* ifndef FISK_CONTINENT_H */
