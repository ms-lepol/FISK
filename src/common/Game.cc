#include "Game.h"
#include "Constants.h"
#include "Continent.h"
#include "Player.h"
#include <cstddef>
#include <iostream>
#include <stdio.h>

namespace fisk {
    Game::Game() {
    }

    PlayerId Game::add_player(Player player) {
        players.push_back(player);
        return PlayerId(players.size()-1);
    }

    CardId Game::add_card(Card card) {
        cards.push_back(card);
        return CardId(cards.size()-1);
    }

    LandId Game::add_land(Land land) {
        lands.push_back(land);
        return LandId(lands.size()-1);
    }

    ContinentId Game::add_continent(Continent continent) {
        continents.push_back(continent);
        return ContinentId(continents.size()-1);
    }

    Player& Game::get_player(PlayerId id) {
        return players[id];
    }

    const Player& Game::get_player(PlayerId id) const{
        return players[id];
    }

    Continent& Game::get_continent(ContinentId id) {
        return continents[id];
    }

    const Continent& Game::get_continent(ContinentId id) const {
        return continents[id];
    }

    Land& Game::get_land(LandId id) {
        return lands[id];
    }

    const Land& Game::get_land(LandId id ) const {
        return lands[id];
    }

    const std::size_t Game::get_nb_lands() const {
        return lands.size();
    }

    const std::size_t Game::get_nb_players() const {
        return players.size();
    }

    size_t Game::nb_lands() const {
        return lands.size();
    }

    void Game::set_current_player(PlayerId id) {
        current_player = id;
    }
    
    PlayerId Game::get_current_player() const {
        return current_player;
    }

    bool Game::is_neighbours_correct() const  {
       bool is_correct = true;
       for (auto continent :continents){
        for (auto land : continent.get_lands()){
            for (auto neighbor : get_land(land).getNeighbors()){
                if (std::find(get_land(neighbor).getNeighbors().begin(), get_land(neighbor).getNeighbors().end(), land) == get_land(neighbor).getNeighbors().end()){
                    std::cout << "Land " << get_land(land).getName() << " is not a neighbor of " << get_land(neighbor).getName() << std::endl;
                    is_correct = false;
                }
            }
        }
       }
        return is_correct;
    }
}
