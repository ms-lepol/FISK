#include <string>
#include <vector>
#include "Land.h"

namespace fisk {

   Land::Land(unsigned nb_units, std::string name, std::vector<unsigned> neighbors, unsigned player_id) {
       this->nb_units = nb_units;
       this->name = name;
       this->neighbors = neighbors;
       this->owner_id = player_id;
   }

}
