#include <vector>

#include "Constants.h"

#include "Player.h"
#include "Land.h"
#include "Card.h"
#include "Continent.h"

class Game {
    std::vector<fisk::Player> players;
    std::vector<Land> lands;
    std::vector<Card> cards;
    std::vector<Continent> continents;

    int game_state;

    public:

    /**
     * add a new player and return the ID
     */
    fisk::PlayerId add_player(Player player);

    /**
     * add a new land and return the ID
     */
    fisk::LandId add_land(Land land);

    /**
     * add a new card and return the ID
     */
    fisk::CardId add_card(Card card);

    /**
     * add a new continent and return the ID
     */
    fisk::ContinentId add_continent(Continent continent);
};
