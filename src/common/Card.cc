#include "Card.h"
#include "Constants.h"
#include "Enums.h"

namespace fisk {

    Card::Card(Type type_unit, LandId land_id):
        type_unit(type_unit),
        land_id(land_id)
    {}

    LandId Card::getLand() const {
        return land_id;
    }

    Type Card::getType() const {
        return type_unit;
    }
}
