#include "Game.h"
#include "Constants.h"
#include "Continent.h"
#include "Enums.h"
#include "Land.h"
#include "Player.h"
#include <algorithm>
#include <csignal>
#include <cstddef>
#include <gf/Id.h>
#include <gf/Log.h>
#include <gf/Random.h>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace fisk {
    Game::Game()
    {
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
        return players.at(id-1);
    }

    Card& Game::get_card(CardId id) {
        return cards.at(id-1);
    }

    const Card& Game::get_card(CardId id) const {
        return cards.at(id-1);
    }

    const Player& Game::get_player(PlayerId id) const{
        return players.at(id-1);
    }

    Continent& Game::get_continent(ContinentId id) {
        return continents.at(id-1);
    }

    const Continent& Game::get_continent(ContinentId id) const {
        return continents.at(id-1);
    }

    Land& Game::get_land(LandId id) {
        return lands.at(id-1);
    }

    const Land& Game::get_land(LandId id ) const {
        return lands.at(id-1);
    }

    const std::size_t Game::get_nb_lands() const {
        return lands.size();
    }

    const std::size_t Game::get_nb_players() const {
        return players.size();
    }

    const std::size_t Game::get_nb_cards() const {
        return cards.size();
    }

    size_t Game::nb_lands() const {
        return lands.size();
    }

    void Game::set_current_player(PlayerId id) {
        current_player = id;
    }

    CardId Game::get_top_card(){
        top_card++;
        return top_card;
    }
    
    PlayerId Game::get_current_player() const {
        return current_player;
    }

    TurnPhase Game::get_current_phase() const {
        return current_phase;
    }

    const Land& Game::get_land_by_name(const std::string& name) const {
        auto it = std::find_if(lands.cbegin(), lands.cend(), [&name](const Land& land) {
                return land.getName() == name;
            });
        if(it == lands.cend()) {
            gf::Log::error("Can't find land '%s'", name.c_str());
            throw "can't find land " + name;
        }
        return *it.base();
    }

    const LandId Game::get_land_id_by_name(const std::string& name) const {
        for(auto i = 0; i<lands.size(); ++i){
            if(lands[i].getName() == name){
                return i+1;
            }
        }
        return gf::InvalidId;
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

    void Game::shuffle_cards() {
        std::random_device random_dev;
        std::mt19937 generator(random_dev());
        std::shuffle(cards.begin(), cards.end(),generator);
    }

    bool Game::are_lands_on_same_territory(LandId a, LandId b) {
        PlayerId player = get_land(a).getOwner();

        if(player != get_land(b).getOwner()) {
            return false;
        }

        std::unordered_set<LandId> visited;
        std::vector<LandId> to_visit = {a};
        do {
            LandId curr = *to_visit.end().base();
            to_visit.pop_back();
            visited.insert(curr);
            for(LandId neighbor: get_land(curr).getNeighbors()) {
                if(get_land(neighbor).getOwner() == player && visited.find(neighbor) == visited.end()) {
                    if(neighbor == b) {
                        return true;
                    }
                    to_visit.push_back(neighbor);
                }
            }
        } while(!to_visit.empty());
        return false;
    }
}
