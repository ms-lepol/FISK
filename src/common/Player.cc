#include "Player.h"

namespace fisk {
    Player::Player(int id_client, int nb_units, gf::Color4f color, std::vector<unsigned> hand){
        this->id_client = id_client;
        this->nb_units = nb_units;
        this->color = color;
        this->hand = hand;
    }
    Player::Player(int id_client, int nb_units, gf::Color4f color, unsigned card...){

    }

    int Player::getId_client(){
        return this->id_client;
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