#include "Card.h"
#include "Constants.h"
#include "Enums.h"
#include <gf/Id.h>

namespace fisk {

    Card::Card(Type type_unit, LandId land_id):
        type_unit(type_unit),
        land_id(land_id)
    {}

    Card::Card() {
        Card(Type::Gunner, gf::InvalidId);
    }

    LandId Card::getLand() const {
        return land_id;
    }

    Type Card::getType() const {
        return type_unit;
    }
}
