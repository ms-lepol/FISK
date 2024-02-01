#include "Player.h"
#include "Constants.h"
#include "FiskColors.h"

namespace fisk {
    Player::Player() {}
    Player::Player(int nb_units, Player::Color color, std::vector<CardId> hand){
        this->nb_units = nb_units;
        this->color = color;
        this->hand = hand;
    }

    Player::Player(int nb_units, Player::Color color, CardId card...){

    }

    int Player::getNb_units(){
        return this->nb_units;
    }

    const uint8_t Player::getColor() const{
        return static_cast<uint8_t>(this->color);
    }

    const gf::Color4f Player::getColor4f() const{
        switch (this->color) {
            case Player::Color::RED:
                return PlayerColor().Orange;
            case Player::Color::BLUE:
                return PlayerColor().Blue;
            case Player::Color::GREEN:
                return PlayerColor().Green;
            case Player::Color::YELLOW:
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
