#ifndef FISK_NETWORK_PROTOCOL_DATA_H
#define FISK_NETWORK_PROTOCOL_DATA_H

#include <string>

#include <gf/Id.h>

namespace fisk {

  struct PlayerData {
    gf::Id id;
    std::string name;
    bool ready = false;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, PlayerData& data) {
    return ar | data.id | data.name | data.ready;
  }

  struct LobbyData {
    gf::Id id;
    std::string name;
    int32_t players;
  };

  template<typename Archive>
  Archive& operator|(Archive& ar, LobbyData& data) {
    return ar | data.id | data.name | data.players;
  }
}

#endif // FISK_NETWORK_PROTOCOL_DATA_H
