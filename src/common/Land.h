#ifndef FISK_LAND_H
#define FISK_LAND_H
#include "Constants.h"
#include <string>
#include <vector>

namespace fisk {

    class Land {
        protected:
            LandId land_id;
            unsigned nb_units;
            std::string name;
            std::vector<LandId> neighbors;
            PlayerId owner_id;
        public:
            Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id);
            unsigned getNb_units();
            std::string getName();
            std::vector<LandId> getNeighbors();
            PlayerId getPlayer_id();
            void setOwner_id(PlayerId player_id);
            void addNeighbor(LandId neighbor);
            void removeNeighbor(LandId neighbor);
            //Actions of the player
            void reinforce(unsigned nb_units);
            void attack(LandId land_id);
            void fortify(LandId land_id);

        };
}
#endif /* ifndef FISK_LAND_H */
