#include <gf/Log.h>
#include <string>
#include <vector>
#include "Constants.h"
#include "Land.h"

namespace fisk {

    Land::Land() {}

    Land::Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id) {
        this->nb_units = nb_units;
        this->name = name;
        this->neighbors = neighbors;
        this->owner_id = player_id;
    }

    std::string Land::getName() const{
         return name;
    }

    unsigned Land::getNb_units() const {
        return nb_units;
    }

    std::vector<LandId> Land::getNeighbors() const {
        return neighbors;
    }

    const PlayerId Land::getOwner() const {
        return owner_id;
    }

    void Land::setOwner_id(PlayerId id) {
        owner_id = id;
    }

    void Land::addNeighbor(LandId id) {
        neighbors.push_back(id);
    }

    void Land::reinforce(unsigned nb_units){
        this->nb_units += nb_units;
    }

    bool Land::attack(Land other){
        if(other.owner_id == owner_id) {
            gf::Log::error("(GAME) Cannot attack already conquered land\n");
            return false;
        }

        //

        return true;
    }   

    bool Land::fortify(Land other){
        if(other.owner_id != owner_id) {
            gf::Log::error("(GAME) Cannot fortify other player's land\n");
            return false;
        }
        //

        return true;
    }
}
