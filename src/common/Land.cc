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

    void Land::setNb_units(unsigned nb) {
        nb_units = nb;
    }

    void Land::rmUnits(unsigned nb){
        nb_units -= nb;
    }

    void Land::addUnits(unsigned nb){
        nb_units += nb;
    }

    void Land::reinforce(unsigned nb){
        addUnits(nb);
    }

    bool Land::attack(Land other, std::vector<int> this_dices, std::vector<int> other_dices){
        // Verification and dice roll has been made before the call of this function
        assert(other.owner_id != owner_id);
        // Calculating dice results
        // asserting vectors contain dices in decreasing order
        auto t_dice = this_dices.begin();
        auto o_dice = other_dices.begin();
        int remaining_troops = this_dices.size();
        while(t_dice != this_dices.end() && o_dice != other_dices.end()){
            if(*t_dice > *o_dice){
                //Win
                other.rmUnits(1);
                if(other.nb_units == 0){
                    //Conquered
                    other.setOwner_id(owner_id);
                    other.setNb_units(remaining_troops);
                    rmUnits(remaining_troops);
                    break;
                }
            }
            else{
                //Lose
                rmUnits(1);
            }
            t_dice++;
            o_dice++;
            remaining_troops--;
        }
        return true;
    }   

    bool Land::fortify(Land other){
        assert(other.owner_id == owner_id);
        //


        return true;
    }
}
