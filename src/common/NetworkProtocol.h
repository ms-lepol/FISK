#ifndef FISK_NETWORK_PROTOCOL_H
#define FISK_NETWORK_PROTOCOL_H

#include <gf/Id.h>
#include <gf/SerializationOps.h>

using namespace gf::literals;

namespace fisk {

/* Server */

struct ServerHello {
static constexpr gf::Id type = "ServerHello"_id;
gf::Id playerId;
};

template<typename Archive>
Archive& operator|(Archive& ar, ServerHello& data) {
return ar | data.playerId;
}

/* Client */

struct ClientHello {
static constexpr gf::Id type = "ClientHello"_id;
std::string name;
};

template<typename Archive>
Archive& operator|(Archive& ar, ClientHello& data) {
return ar | data.name;
}

struct ClientDisconnect {
static constexpr gf::Id type = "ClientDisconnect"_id;
};

template<typename Archive>
Archive& operator|(Archive& ar, ClientDisconnect&) {
return ar;
}

}

#endif /* FISK_NETWORK_PROTOCOL_H */