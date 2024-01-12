#include "Card.h"
#include "Constants.h"

namespace fisk {
    fisk::LandId Card::getLand() const {
        return land_id;
    }

    fisk::Type Card::getType() const {
        return type_unit;
    }

    template<typename S>
    S& operator|(S& sa, Card const& card) {
        return sa | card.getType() | card.getLand();
    }
}
