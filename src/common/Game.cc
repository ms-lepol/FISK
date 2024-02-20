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

    const int32_t Game::get_nb_lands() const {
        return static_cast<int32_t>(lands.size());
    }

    const int32_t Game::get_nb_players() const {
        return static_cast<int32_t>(players.size());
    }

    const int32_t Game::get_nb_cards() const {
        return static_cast<int32_t>(cards.size());
    }

    int32_t Game::nb_lands() const {
        return static_cast<int32_t>(lands.size());
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
        bool is_neighbours_correct = true;
        for(int i = 1; i < lands.size()+1; i++) {
            auto& land = get_land(i);
            for(LandId neighbor : land.getNeighbors()) {
                auto& LB = get_land(neighbor);
                for (int j = 0; j < LB.getNeighbors().size()+1; j++) {
                    if (j == LB.getNeighbors().size()) {
                        gf::Log::error("Land %s and %s are not neighbours\n", get_land(i).getName().c_str(), get_land(neighbor).getName().c_str());
                        is_neighbours_correct= false;
                    }
                    if (LB.getNeighbors()[j] == i) {
                        break;
                    }
                }
            }
        }
        return is_neighbours_correct;
    }

    bool Game::is_neighbour(LandId a, LandId b) const{
        auto n = get_land(a).getNeighbors();
        auto find = std::find(n.begin(), n.end(), b);
        return (find != n.end());
    }

    void Game::next_phase() {
        switch (current_phase) {
            case TurnPhase::Fortify:
                current_phase = TurnPhase::Attack;
                break;
            case TurnPhase::Attack:
                current_phase = TurnPhase::Reinforce;
                break;
            case TurnPhase::Reinforce:
                current_phase = TurnPhase::Fortify;
                current_player = (current_player + 1) % (get_nb_players() + 1);
                if(current_player == 0) current_player = 1;
                break;
            case TurnPhase::End:
            default:
                gf::Log::error("(GAME) Error when changing turn\n");
                break;
        }
    }

    void Game::shuffle_cards() {
        std::random_device random_dev;
        std::mt19937 generator(random_dev());
        std::shuffle(cards.begin(), cards.end(),generator);
    }

    void Game::attack(LandId atk, LandId def, std::vector<int>& attack_dices, std::vector<int>& defence_dices){
        // Verification and dice roll has been made before the call of this function
        auto& attack = get_land(atk);
        auto& defence = get_land(def);
        gf::Log::debug("Start attack\n");
        assert(defence.getOwner() != attack.getOwner());
        //
        sort(attack_dices.begin(), attack_dices.end(), std::greater<int>());
        sort(defence_dices.begin(), defence_dices.end(), std::greater<int>());
        for(auto i : attack_dices){
            gf::Log::debug("attack dice : %i\n", i);
        }
        for(auto i : defence_dices){
            gf::Log::debug("defence dice : %i\n", i);
        }
        // Calculating dice results
        auto t_dice = attack_dices.begin();
        auto o_dice = defence_dices.begin();
        int remaining_troops = attack_dices.size();
        gf::Log::debug("(BEFORE) Defence : %lu %u; Attack : %lu, %u\n", defence.getOwner(), defence.getNb_units(), attack.getOwner(), attack.getNb_units());
        while(t_dice != attack_dices.end() && o_dice != defence_dices.end()){
            gf::Log::debug("Remaining troops : %i\n", remaining_troops);
            gf::Log::debug("%i, %i\n", *t_dice, *o_dice);
            if(*t_dice > *o_dice){
                //Win
                gf::Log::debug("Win\n");
                defence.rmUnits(1);
                if(defence.getNb_units() == 0){
                    gf::Log::debug("Conquered\n");
                    //Conquered
                    defence.setOwner_id(attack.getOwner());
                    defence.setNb_units(remaining_troops);
                    attack.rmUnits(remaining_troops);
                    gf::Log::debug("attack conquered\n");
                    return;
                }
            }
            else{
                //Lose
                gf::Log::debug("Lose\n");
                attack.rmUnits(1);
            }
            t_dice++;
            o_dice++;
            remaining_troops--;
        }
        gf::Log::debug("attack did not conquered\n");
        return;
    }   

    bool Game::are_lands_on_same_territory(LandId a, LandId b) const {
        gf::Log::debug("(GAME) DFS from %s to %s.\n", get_land(a).getName().c_str(), get_land(b).getName().c_str());
        PlayerId player = get_land(a).getOwner();

        if(player != get_land(b).getOwner()) {
            return false;
        }

        std::unordered_set<LandId> visited;
        std::vector<LandId> to_visit = {a};
        while(!to_visit.empty()) {
            LandId curr = to_visit[to_visit.size()-1];
            to_visit.pop_back();
            visited.insert(curr);
            for(LandId neighbor : get_land(curr).getNeighbors()) {
                gf::Log::debug("(GAME) Analyzing %s\n", get_land(neighbor).getName().c_str());
                if(get_land(neighbor).getOwner() == player && visited.find(neighbor) == visited.end()) {
                    if(neighbor == b) {
                        gf::Log::debug("(GAME) There is a path between %s and %s\n", get_land(a).getName().c_str(), get_land(b).getName().c_str());
                        return true;
                    }
                    to_visit.push_back(neighbor);
                }
            }
        }
        gf::Log::debug("(GAME) No path found between %s and %s\n", get_land(a).getName().c_str(), get_land(b).getName().c_str());
        return false;
    }

    bool Game::can_attack() const {
        for(auto land : lands) {
            if(land.getOwner() == current_player && land.getNb_units() > 1) return true;
        }
        return false;
    }
}
