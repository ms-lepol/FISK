#include "Constants.h"
#ifndef FISK_CARD_H
#define FISK_CARD_H

#include "gf/Serialization.h"
#include "Enums.h"

namespace fisk {
    class Card {
        fisk::Type type_unit;
        LandId land_id;

        public:

        fisk::Type getType() const;
        LandId getLand() const;
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Card const& card);
}

#endif /* ifndef FISK_CARD_H */
