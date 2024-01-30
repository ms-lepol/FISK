#include "GameInstance.h"
#include "ServerPlayer.h"
#include <algorithm>
#include <gf/Color.h>
#include <gf/Log.h>
#include <gf/Packet.h>
#include <gf/Vector.h>
#include <memory>
#include <vector>

namespace fisk {

    GameInstance::GameInstance(std::unique_ptr<Game> model):
        model(std::move(*model)) {
    }

    void GameInstance::start() {
        gf::Log::info("GameInstance started");

        const int nb_land_by_player = 4;
        const auto player_colors = gf::vec(
            gf::Color::Red,
            gf::Color::Blue,
            gf::Color::Green,
            gf::Color::Yellow
        );

        for(unsigned i=0; i < this->getPlayers().size(); ++i) {
            Player player(0, player_colors[i], {});
            model.add_player(player);
        }

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
