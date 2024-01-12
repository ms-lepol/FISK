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

}
