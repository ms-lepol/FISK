#ifndef FISK_GAME_H
#define FISK_GAME_H
#include <vector>

#include "Constants.h"

#include "Player.h"
#include "Land.h"
#include "Card.h"
#include "Continent.h"

namespace fisk {

    class Game {
        std::vector<Player> players;
        std::vector<Land> lands;
        std::vector<Card> cards;
        std::vector<Continent> continents;

        int game_state;

        public:

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

        const Player& get_player(PlayerId player) const;
        const Land& get_land(LandId land) const;
        const Card& get_card(CardId card) const;
        const Continent& get_continent(ContinentId continent) const;
    };

}
#endif /* ifndef FISK_GAME_H */
