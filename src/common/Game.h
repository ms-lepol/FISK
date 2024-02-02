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

            GameState game_state;
            PlayerId current_player;
            TurnPhase current_phase;
            Land selection;

            gf::Random m_random;

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
            Land& get_selection();
            Card& get_card(CardId card);
            Continent& get_continent(ContinentId continent);
            PlayerId get_current_player() const;
            TurnPhase get_current_phase() const;


            void set_current_player(PlayerId player);

            const std::size_t get_nb_lands() const;
            const std::size_t get_nb_players() const;

            bool is_neighbours_correct() const;


            const Player& get_player(PlayerId player) const;
            const Land& get_land(LandId land) const;
            const Card& get_card(CardId card) const;
            const Continent& get_continent(ContinentId continent) const;

            size_t nb_lands() const;
    
            template<typename S>
            void serialisation(S& sa) {
                sa | cards | players | lands | continents | current_player | current_phase | selection;
            }
    };

    template<typename S> // Serializer or Deserializer
    S& operator|(S& sa, Game& game) {
        game.serialisation(sa);
        return sa;
    }

}
#endif /* ifndef FISK_GAME_H */
