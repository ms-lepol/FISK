#include "Player.h"
#include "Constants.h"
#include "FiskColors.h"
#include "Game.h"
#include <algorithm>
#include <gf/Log.h>
#include <vector>

namespace fisk {
    Player::Player() {
        this->nb_units = 0;
        this->color = Color::NEUTRAL;
        this->hand = {};
    }
    Player::Player(int nb_units, Player::Color color, std::vector<CardId> hand):
        nb_units(nb_units),
        color(color),
        hand(hand)
    {}

    int Player::getNb_units(){
        return this->nb_units;
    }

    int Player::getNb_units() const{
        return this->nb_units;
    }

    Player::Color Player::getColor() const{
        return color;
    }

    std::vector<CardId> Player::getHand() const{
        return hand;
    }

    const gf::Color4f Player::getColor4f() const{
        switch (color) {
            case Color::RED:
                
                return PlayerColor().Orange;
            case Color::BLUE:
              
                return PlayerColor().Blue;
            case Color::GREEN:
                
                return PlayerColor().Green;
            case Color::YELLOW:
               
                return PlayerColor().Yellow;
        }
        return PlayerColor().Neutral;
    }

    void Player::setNb_units(int nb_units){
        this->nb_units = nb_units;
    }

    void Player::drawCard(CardId id){
        if(hand.size() == 5){
            gf::Log::debug("Hand full\n");
            return;
        }
        gf::Log::debug("drew card %lu\n", id);
        hand.push_back(id);
    }
    void Player::playCard(CardId a, CardId b, CardId c){
        this->nb_units += 15;
        //
        for(int i = 0; i < 2; ++i){
            for(auto curr = hand.begin(); curr < hand.end(); ++curr){
                if(*curr == a || *curr == b || *curr == c) hand.erase(curr);
            }
        }
    }
};
