#include <string>
#include <vector>
#include "Constants.h"
#include "Continent.h"

namespace fisk {
    Continent::Continent(std::string name, std::vector<LandId> lands):
        name(name),
        lands(lands)
    {}

    std::string Continent::getName() {
        return name;
    }

    void Continent::add_land(LandId land) {
        lands.push_back(land);
    }
}
