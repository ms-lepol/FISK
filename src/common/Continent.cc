#include <string>
#include <vector>
#include "Constants.h"
#include "Continent.h"

namespace fisk {

    Continent::Continent(){}

    Continent::Continent(std::string name, std::vector<LandId> lands,int bonus):
        name(name),
        lands(lands),
        bonus(bonus)
    {

    }

    int Continent::get_bonus() const {
        return bonus;
    }

    std::string Continent::getName() const{
        return name;
    }

    std::vector<LandId> Continent::get_lands() const {
        return lands;
    }
    void Continent::add_land(LandId land) {
        lands.push_back(land);
    }
}
