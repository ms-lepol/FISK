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

    bool Land::attack(Land& other, std::vector<int>& this_dices, std::vector<int>& other_dices){
        // Verification and dice roll has been made before the call of this function
        gf::Log::debug("attacking\n");
        assert(other.owner_id != owner_id);
        for(auto i : this_dices){
            gf::Log::debug("attack dice : %i\n", i);
        }
        //
        gf::Log::debug("Sorting vectors\n");
        sort(this_dices.begin(), this_dices.end(), std::greater<int>());
        sort(other_dices.begin(), other_dices.end(), std::greater<int>());
        // Calculating dice results
        gf::Log::debug("initializing some variables\n");
        auto t_dice = this_dices.begin();
        auto o_dice = other_dices.begin();
        int remaining_troops = this_dices.size();
        gf::Log::debug("analizing dices\n");
        while(t_dice != this_dices.end() && o_dice != other_dices.end()){
            gf::Log::debug("Remaining troops : %i\n", remaining_troops);
            gf::Log::debug("%i, %i\n", *t_dice, *o_dice);
            if(*t_dice > *o_dice){
                //Win
                gf::Log::debug("Win\n");
                other.rmUnits(1);
                if(other.nb_units == 0){
                    gf::Log::debug("Conquered\n");
                    //Conquered
                    other.setOwner_id(owner_id);
                    other.setNb_units(remaining_troops);
                    rmUnits(remaining_troops);
                    break;
                }
            }
            else{
                //Lose
                gf::Log::debug("Lose\n");
                rmUnits(1);
            }
            t_dice++;
            o_dice++;
            remaining_troops--;
        }
        gf::Log::debug("End of attack\n");
        return true;
    }   

    bool Land::reinforce(Land other){
        assert(other.owner_id == owner_id);
        //


        return true;
    }
}
