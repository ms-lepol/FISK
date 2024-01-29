#include "gf/SerializationOps.h"
#include "Constants.h"
#include <cstdint>
#ifndef FISK_CARD_H
#define FISK_CARD_H

#include "Enums.h"

namespace fisk {
    class Card {
        fisk::Type type_unit;
        LandId land_id;

        public:

        Card();
        Card(Type type_unit, LandId land_id);
        Type getType() const;
        LandId getLand() const;

        template<typename S>
        void serialisation(S& sa) {
            sa | type_unit | land_id;
        }
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Card& card) {
        card.serialisation(sa);
        return sa;
    }
}

#endif /* ifndef FISK_CARD_H */
