#ifndef FISK_NETWORK_PROTOCOL_H
#define FISK_NETWORK_PROTOCOL_H

#include <gf/Id.h>
#include <gf/SerializationOps.h>

using namespace gf::literals;

struct ClientDisconnect {
static constexpr gf::Id type = "ClientDisconnect"_id;
};

template<typename Archive>
Archive& operator|(Archive& ar, ClientDisconnect&) {
return ar;
}

#endif /* FISK_NETWORK_PROTOCOL_H */
