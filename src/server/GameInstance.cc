#include "GameInstance.h"
#include "ServerPlayer.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <gf/Color.h>
#include <gf/Id.h>
#include <gf/Log.h>
#include <gf/Packet.h>
#include <gf/Vector.h>
#include <memory>
#include <vector>
#include "../common/FiskColors.h"


namespace fisk {

    GameInstance::GameInstance(std::unique_ptr<Game> model):
        model(std::move(*model)) {
    }

    void GameInstance::start() {
        gf::Log::info("GameInstance started");

        const int nb_land_by_player = 4;
        std::vector<PlayerId> player_ids ;
        //Initialize players
        for(unsigned i=0; i < this->getPlayers().size(); ++i) {
            Player player(0, static_cast<Player::Color>(i), {});
            player_ids.push_back(model.add_player(player));
        }
        //Initialize lands
        unsigned nb_lands = model.get_nb_lands()  ;
        unsigned nb_players = this->getPlayersCount();

        gf::Log::info("Nb Players: %d\n", nb_players);
        for (unsigned i = 0; i < nb_players; i++) {
            for (unsigned j = 0; j < nb_land_by_player; j++) {
                bool placed = false;
                while (!placed) {
                    unsigned rand_land = rand() % nb_lands;
                    if (model.get_land(rand_land).getOwner() == gf::InvalidId) {
                        model.get_land(rand_land).setOwner_id(player_ids[i]);
                        
                        placed = true;
                    }
                }
                ;
            }
        }
        model.set_current_player(PlayerId(1));

        broadcast(model);
    }

    void GameInstance::update(ServerPlayer& player, gf::Packet& packet) {
        switch (packet.getType()) {
            case ClientGameClickLand::type: {
                //
            }

            case ClientGameCardButton::type: {
                //
            }
        }
    }

    bool GameInstance::isFinished() {
        return false;
    }
}
