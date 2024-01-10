#include <string>
#include <vector>
#include "Continent.h"

namespace fisk {
    Continent::Continent(std::string name, std::vector<unsigned> lands):
        name(name),
        lands(lands)
    {}

    std::string Continent::getName() {
        return name;
    }
}
