#include "Player.h"
#include "Constants.h"
#include "FiskColors.h"
#include <gf/Log.h>

namespace fisk {
    Player::Player() {}
    Player::Player(int nb_units, Player::Color color, std::vector<CardId> hand):
        nb_units(nb_units),
        color(color),
        hand(hand)
    {}

    int Player::getNb_units(){
        return this->nb_units;
    }

    Player::Color Player::getColor() const{
        return color;
    }

    const gf::Color4f Player::getColor4f() const{
        switch (this->color) {
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
    void drawCard(){
        // TODO
    }
    void playCard(){
        // TODO
    }
};
