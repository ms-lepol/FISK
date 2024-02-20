#ifndef FISK_GAME_H
#define FISK_GAME_H
#include <cstddef>
#include <gf/Id.h>
#include <iterator>
#include <vector>

#include "Constants.h"

#include "Player.h"
#include "Land.h"
#include "Card.h"
#include "Continent.h"
#include "Enums.h"

using namespace gf::literals;

namespace fisk {

    class Game {
        private :
            std::vector<Player> players;
            std::vector<Land> lands;
            std::vector<Card> cards;
            std::vector<Continent> continents;

            CardId top_card = 0;

            GameState game_state;
            PlayerId current_player;
            TurnPhase current_phase = TurnPhase::Fortify;

        public:

            static constexpr gf::Id type = "Game"_id;

            Game();

            /**
            * add a new player and return the ID
            */
            PlayerId add_player(Player player);

            /**
            * add a new land and return the ID
            */
            LandId add_land(Land land);

            /**
            * add a new card and return the ID
            */
            CardId add_card(Card card);

            /**
            * add a new continent and return the ID
            */
            ContinentId add_continent(Continent continent);

            Player& get_player(PlayerId player);
            Land& get_land(LandId land);
            Card& get_card(CardId card);
            Continent& get_continent(ContinentId continent);
            PlayerId get_current_player() const;
            TurnPhase get_current_phase() const;

            CardId get_top_card();

            void set_current_player(PlayerId player);

            const int32_t get_nb_lands() const;
            const int32_t get_nb_players() const;
            const int32_t get_nb_cards() const;

            bool is_neighbours_correct() const;
            bool is_neighbour(LandId a, LandId b) const;
            void attack(LandId atk, LandId def, std::vector<int>& attack_dices, std::vector<int>& defence_dices);
            bool can_attack() const;

            const Player& get_player(PlayerId player) const;
            const Land& get_land(LandId land) const;
            const Land& get_land_by_name(const std::string& name) const;
            const LandId get_land_id_by_name(const std::string& name) const;
            const Card& get_card(CardId card) const;
            const Continent& get_continent(ContinentId continent) const;

            bool are_lands_on_same_territory(LandId a, LandId b) const;
            bool is_finished() const;
            void shuffle_cards();

            /**
             * @brief Change the current game phase to the next one
             */
            void next_phase();

            int32_t nb_lands() const;
    
            template<typename S>
            void serialisation(S& sa) {
                sa | cards | players | lands | continents | current_player | current_phase;
            }
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Game& game) {
        game.serialisation(sa);
        return sa;
    }

}
#endif /* ifndef FISK_GAME_H */
