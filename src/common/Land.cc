#include <string>
#include <vector>
#include "Constants.h"
#include "Land.h"

namespace fisk {

   Land::Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id) {
       this->nb_units = nb_units;
       this->name = name;
       this->neighbors = neighbors;
       this->owner_id = player_id;
   }

    std::string Land::getName() {
         return name;
    }

    unsigned Land::getNb_units() {
        return nb_units;
    }

    std::vector<LandId> Land::getNeighbors() {
        return neighbors;
    }

    void Land::addNeighbor(LandId id) {
        neighbors.push_back(id);
    }
}
