#include <gf/Id.h>
#include <gf/Log.h>
#include <gf/Dice.h>
#include <string>
#include <vector>
#include "Constants.h"
#include "Land.h"

namespace fisk {

    Land::Land()
    {
        nb_units = 1;
        name = "";
        neighbors = {};
        owner_id = gf::InvalidId;
    }

    Land::Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id)
    {
        this->nb_units = 1;
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

    void Land::setNb_units(unsigned nb) {
        nb_units = nb;
    }

    void Land::rmUnits(unsigned nb){
        nb_units -= nb;
        if (nb_units <= 0) nb_units = 1; // Should never happen ! >:(
    }

    void Land::addUnits(unsigned nb){
        nb_units += nb;
    }

    bool Land::sameAs(Land& other){
        return name.compare(other.name) == 0;
    }

    void Land::fortify(unsigned nb){
        addUnits(nb);
    }

    bool Land::reinforce(Land other){
        assert(other.owner_id == owner_id);
        //


        return true;
    }
}
