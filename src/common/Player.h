#ifndef FISK_PLAYER_H
#define FISK_PLAYER_H
#include "Constants.h"

#include <gf/Color.h>
#include <sys/types.h>
#include <vector>
namespace fisk {

    class Game;

    class Player {
        private:
            unsigned nb_units;
            std::vector<CardId> hand;
        public:
            enum class Color : uint8_t{
                YELLOW = 0,
                RED = 1,
                BLUE = 2,
                GREEN = 3,
                NEUTRAL = 4
            } color;

            Player();
            Player(int nb_units, Player::Color color, std::vector<CardId> hand);
            int getId_client();
            int getNb_units() const;
            int getNb_units();
            void setNb_units(unsigned nb);
            Player::Color getColor() const;
            const gf::Color4f getColor4f() const;
            void setNb_units(int nb_units);
            std::vector<CardId> getHand() const;

            void drawCard(CardId id);
            void playCard();

            template<typename S>
            void serialisation(S& sa) {
                sa | nb_units | color | hand;
            }
    };

    template<typename S>
    S& operator|(S& sa, Player& player) {
        player.serialisation(sa);
        return sa;
    }
}
#endif /* ifndef FISK_PLAYER_H */
