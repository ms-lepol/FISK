#include <gf/Log.h>
#include <gf/Dice.h>
#include <string>
#include <vector>
#include "Constants.h"
#include "Land.h"

namespace fisk {

    Land::Land()
    {}

    Land::Land(unsigned nb_units, std::string name, std::vector<LandId> neighbors, PlayerId player_id)
    {
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

    void Land::setNb_units(unsigned nb_units) {
        this->nb_units = nb_units;
    }

    void Land::reinforce(unsigned nb_units){
        this->nb_units += nb_units;
    }

    bool Land::attack(Land other, std::vector<int> attack_dices, std::vector<int> defence_dices){
        // Verification and dice roll has been made before the call of this function
        assert(other.owner_id != owner_id);
        // Calculating dice results
        auto a_dice = attack_dices.begin();
        auto d_dice = defence_dices.begin();

        while(d_dice != defence_dices.end() && a_dice != attack_dices.end()){
            
        }

        return true;
    }   

    bool Land::fortify(Land other){
        assert(other.owner_id == owner_id);
        //


        return true;
    }
}
