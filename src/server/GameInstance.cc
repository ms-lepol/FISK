#include "GameInstance.h"
#include <gf/Dice.h>
#include <map>
#include "ServerPlayer.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <gf/Color.h>
#include <gf/Id.h>
#include <gf/Log.h>
#include <gf/Packet.h>
#include <gf/Vector.h>
#include <memory>
#include <vector>
#include <cinttypes>

#include "../common/FiskColors.h"


namespace fisk {

    GameInstance::GameInstance(std::unique_ptr<Game> model, gf::Random& random):
    model(std::move(*model)),
    m_random(random),
    ready(false)
    {
    }

    void GameInstance::start() {
        gf::Log::info("(GAME) GameInstance started\n");

        const int nb_land_by_player = 4;
        std::vector<PlayerId> player_ids ;
        //Initialize players
        for(unsigned i=0; i < this->getPlayers().size(); ++i) {
            srv_to_model_id[getPlayers()[i].id] = i + 1;
            Player player(0, static_cast<Player::Color>(i), {});
            gf::Log::info("Player %d - color : %hhu \n", i, static_cast<Player::Color>(i));
            gf::Log::info("Player %d - color : %hhu \n", i, player.getColor());
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
        model.get_player(1).drawCard(1);


        
        for(auto& player: getPlayers()) {
            ServerHello hello;
            hello.playerId = srv_to_model_id.at(player.id);
            send(player.id, hello);
        }

        ready = true;
    }

    void GameInstance::update(ServerPlayer& player, gf::Packet& packet) {
        if(!ready) return;
        if(player.id != model.get_current_player()) {
            gf::Log::info("(SERVER GAME) This is not your turn to play\n");
            return;
        }
        TurnPhase curr_phase = model.get_current_phase();
        switch (packet.getType()) {
            case ClientGameSendFortify::type: {
                gf::Log::debug("(SERVER GAME) Received Fortify from player {%" PRIX64 "}...\n", player.id);
                //
                if(curr_phase != TurnPhase::Fortify) break;
                //
                auto data = packet.as<ClientGameSendFortify>();
                //
                model.get_land(data.land_id).fortify(data.nb);
                model.get_player(player.id).setNb_units(model.get_player(player.id).getNb_units() - data.nb);
                //
                if(model.get_player(player.id).getNb_units() == 0) model.next_phase();
                break;
            }
            case ClientGameSendAttack::type: {
                gf::Log::debug("(SERVER GAME) Received Attack from player {%" PRIX64 "}...\n", player.id);
                //
                auto data = packet.as<ClientGameSendAttack>();
                //
                auto attacker = model.get_land(data.attacking_land_id);
                auto defender = model.get_land(data.defending_land_id);
                //
                std::vector<int> attacker_dices;
                std::vector<int> defender_dices;
                gf::Dice d6(6);
                //
                for(auto i = 0; i<data.attacking_nb_dice; ++i){
                    attacker_dices.push_back(d6.roll(m_random));
                    if(defender.getNb_units() > i){ // Maximum amount of dices for the defender
                        defender_dices.push_back(d6.roll(m_random));
                    }
                }
                //
                attacker.attack(defender, attacker_dices, defender_dices);
                //
                model.next_phase();
                break;
            }
        }
        
        broadcast(model); // update every clients ! MAY NOT WORK SINCE SERVER_CLIENT NOT INITIALIZED IN GAMEINSTANCE !
    }

    bool GameInstance::isFinished() {
        return false;
    }
}
