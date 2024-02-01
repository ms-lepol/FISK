#ifndef FISK_LAND_H
#define FISK_LAND_H
#include "Constants.h"
#include <gf/Dice.h>
#include <gf/Keyboard.h>
#include <gf/Random.h>
#include <gf/Ref.h>
#include <string>
#include <vector>

namespace fisk {

    class Land {
        protected:
            unsigned nb_units;
            std::string name;
            std::vector<LandId> neighbors;
            PlayerId owner_id;
        public:
            Land();
            Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id);
            unsigned getNb_units() const;
            void setNb_units(unsigned nb_units);
            std::string getName() const;
            std::vector<LandId> getNeighbors() const;
            const PlayerId getOwner() const;
            void setOwner_id(PlayerId player_id);

            void addNeighbor(LandId neighbor);
            void removeNeighbor(LandId neighbor);
            //Actions of the player
            void reinforce(unsigned nb_units);
            bool attack(Land other);
            bool fortify(Land other);

            template<typename S>
            void serialisation(S& sa) {
                sa | nb_units | name | owner_id | neighbors;
            }
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Land& land) {
        land.serialisation(sa);
        return sa;
    }
}
#endif /* ifndef FISK_LAND_H */
