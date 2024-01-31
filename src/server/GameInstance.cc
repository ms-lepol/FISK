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
        const auto player_colors = gf::vec(
            PlayerColor().Yellow,
            PlayerColor().Orange,
            PlayerColor().Blue,
            PlayerColor().Green
        );
        //Initialize players
        for(unsigned i=0; i < this->getPlayers().size(); ++i) {
            Player player(0, player_colors[i], {});
            model.add_player(player);
        }
        //Initialize lands
        unsigned nb_lands = model.get_nb_lands()  ;
        unsigned nb_players = this->getPlayers().size();

        for (unsigned i = 0; i <nb_players; ++i) {
            for (unsigned j = 0; j < nb_land_by_player; ++j) {
                bool placed = false;
                while (!placed) {
                    unsigned rand_land = rand() % nb_lands;
                    if (model.get_land(rand_land).getOwner() == gf::InvalidId) {
                        model.get_land(rand_land).setOwner_id(PlayerId(i));
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
