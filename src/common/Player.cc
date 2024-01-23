#include "Player.h"
#include "Constants.h"

namespace fisk {
    Player::Player(int nb_units, gf::Color4f color, std::vector<CardId> hand){
        this->nb_units = nb_units;
        this->color = color;
        this->hand = hand;
    }
    Player::Player(int nb_units, gf::Color4f color, CardId card...){

    }

    int Player::getNb_units(){
        return this->nb_units;
    }

    gf::Color4f Player::getColor(){
        return this->color;
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
