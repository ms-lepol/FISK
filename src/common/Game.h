#include <vector>

#include "Player.h"
#include "Land.h"
#include "Card.h"
#include "Continent.h"

class Game {
    std::vector<Player> players;
    std::vector<Land> lands;
    std::vector<Card> cards;
    std::vector<Continent> continents;

    int game_state;

    public:

    /**
     * add a new player and return the ID
     */
    unsigned add_player(Player player);

    /**
     * add a new land and return the ID
     */
    unsigned add_land(Land land);

    /**
     * add a new card and return the ID
     */
    unsigned add_card(Card card);

    /**
     * add a new continent and return the ID
     */
    unsigned add_continent(Continent continent);
};
