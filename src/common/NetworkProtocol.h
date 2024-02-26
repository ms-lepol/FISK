#ifndef FISK_NETWORK_PROTOCOL_H 
#define FISK_NETWORK_PROTOCOL_H

#include <gf/Id.h>
#include <gf/SerializationOps.h>

#include "Game.h"
#include "Land.h"
#include "NetworkProtocolData.h"

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

    struct ServerListLobbys {
        static constexpr gf::Id type = "ServerListLobbys"_id;
        std::vector<LobbyData> lobbys;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerListLobbys& data) {
            return ar | data.lobbys;
        }

    struct ServerJoinLobby {
        static constexpr gf::Id type = "ServerJoinLobby"_id;
        gf::Id lobby;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerJoinLobby& data) {
            return ar | data.lobby;
        }

    struct ServerLeaveLobby {
        static constexpr gf::Id type = "ServerLeaveLobby"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerLeaveLobby&) {
            return ar;
        }

    struct ServerReady {
        static constexpr gf::Id type = "ServerReady"_id;
        bool ready;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerReady& data) {
            return ar | data.ready;
        }

    struct ServerListLobbyPlayers {
        static constexpr gf::Id type = "ServerListLobbyPlayers"_id;
        std::vector<PlayerData> players;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerListLobbyPlayers& data) {
            return ar | data.players;
        }

    struct ServerStartGame {
        static constexpr gf::Id type = "ServerStartGame"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerStartGame&) {
            return ar;
        }

    struct ServerStopGame {
        static constexpr gf::Id type = "ServerStopGame"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerStopGame&) {
            return ar;
        }

    struct ServerError {
        static constexpr gf::Id type = "ServerError"_id;

        enum Type : uint16_t {
            PlayerAlreadyInLobby,
            PlayerAlreadyReady,
            PlayerNotInLobby,
            UnknownLobby,
            FullLobby,
            GameAlreadyStarted,
        };

        Type reason;
    };

    inline std::string serverErrorString(ServerError::Type type) {
        switch (type) {
            case ServerError::Type::PlayerAlreadyInLobby:
                return "You are already in lobby.";

            case ServerError::Type::PlayerAlreadyReady:
                return "You are already ready.";

            case ServerError::Type::PlayerNotInLobby:
                return "You are not in lobby.";

            case ServerError::Type::UnknownLobby:
                return "The lobby is unknown.";

            case ServerError::Type::FullLobby:
                return "The lobby is full.";

            case ServerError::Type::GameAlreadyStarted:
                return "The game is already started.";
        }

        assert(false);
        return "";
    }

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerError& data) {
            return ar | data.reason;
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

    struct ClientCreateLobby {
        static constexpr gf::Id type = "ClientCreateLobby"_id;
        std::string name;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientCreateLobby& data) {
            return ar | data.name;
        }

    struct ClientJoinLobby {
        static constexpr gf::Id type = "ClientJoinLobby"_id;
        gf::Id lobby;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientJoinLobby& data) {
            return ar | data.lobby;
        }

    struct ClientLeaveLobby {
        static constexpr gf::Id type = "ClientLeaveLobby"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientLeaveLobby&) {
            return ar;
        }

    struct ClientReady {
        static constexpr gf::Id type = "ClientReady"_id;
        bool ready;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientReady& data) {
            return ar | data.ready;
        }


    /* Server Game */

    struct ServerGameAskTroops {
        static constexpr gf::Id type = "ServerGameAskTroops"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerGameAskTroops& data) {
            return ar;
        }

    struct ServerGameSendInit {
        static constexpr gf::Id type = "ServerGameSendInit"_id;
        Game model;

    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerGameSendInit& data) {
            return ar | data.model;
        }

    struct ServerGameSendTurnStart {
        static constexpr gf::Id type = "ServerGameSendTurnStart"_id;
        CardId card;
        int nb_troops;

    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ServerGameSendTurnStart& data) {
            return ar | data.card | data.nb_troops;
        }
        
    // Client game

    struct ClientGameSendFortify {
        static constexpr gf::Id type = "ClientGameSendFortify"_id;
        LandId land_id;
        int nb;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientGameSendFortify& data) {
            return ar | data.land_id | data.nb;
        } 

    struct ClientGameSendAttack {
        static constexpr gf::Id type = "ClientGameSendAttack"_id;
        LandId attacking_land_id;
        LandId defending_land_id;
        unsigned attacking_nb_dice;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientGameSendAttack& data) {
            return ar | data.attacking_land_id | data.defending_land_id | data.attacking_nb_dice;
        } 

    struct ClientGameEndAttack {
        static constexpr gf::Id type = "ClientGameEndAttack"_id;
    };
   
    template<typename Archive>
        Archive& operator|(Archive& ar, ClientGameEndAttack& data) {
            return ar;
        } 

    struct ClientGameSendReinforce {
        static constexpr gf::Id type = "ClientGameSendReinforce"_id;
        LandId from;
        LandId target;
        int nb_troops;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientGameSendReinforce& data) {
            return ar | data.from | data.target | data.nb_troops;
        } 
    
    struct ClientGameEndReinforce {
        static constexpr gf::Id type = "ClientGameEndReinforce"_id;
    };

    template<typename Archive>
        Archive& operator|(Archive& ar, ClientGameEndReinforce& data) {
            return ar;
        } 

}   

#endif /* FISK_NETWORK_PROTOCOL_H */
