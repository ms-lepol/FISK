#include "gf/SerializationOps.h"
#include "Constants.h"
#include <cstdint>
#ifndef FISK_CARD_H
#define FISK_CARD_H

#include "Enums.h"

namespace fisk {
    class Card {
        public:

        fisk::Type type_unit;
        LandId land_id;

        Card(Type type_unit, LandId land_id);
        Type getType() const;
        LandId getLand() const;
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Card& card) {
        return sa | card.type_unit | card.land_id;
    }
}

#endif /* ifndef FISK_CARD_H */
