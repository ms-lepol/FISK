#include "Game.h"
#include "Constants.h"
#include "Continent.h"
#include "Player.h"

namespace fisk {
    Game::Game() {
    }

    PlayerId Game::add_player(Player player) {
        players.push_back(player);
        return PlayerId(players.size());
    }

    CardId Game::add_card(Card card) {
        cards.push_back(card);
        return CardId(cards.size());
    }

    LandId Game::add_land(Land land) {
        lands.push_back(land);
        return LandId(lands.size());
    }

    ContinentId Game::add_continent(Continent continent) {
        continents.push_back(continent);
        return ContinentId(continents.size());
    }

    Player& Game::get_player(PlayerId id) {
        return players[id];
    }

    Continent& Game::get_continent(ContinentId id) {
        return continents[id];
    }

    Land& Game::get_land(LandId id) {
        return lands[id];
    }
}
