#ifndef FISK_PLAYER_H
#define FISK_PLAYER_H
#include "Constants.h"
#include <gf/Color.h>
#include <vector>
namespace fisk {
    class Player {
        private:
            PlayerId id_client;
            unsigned nb_units;
            gf::Color4f color;
            std::vector<CardId> hand;
        public:
            Player(PlayerId id_client, int nb_units, gf::Color4f color, std::vector<CardId> hand);
            Player(PlayerId id_client, int nb_units, gf::Color4f color, CardId card...);
            int getId_client();
            int getNb_units();
            gf::Color4f getColor();
            void setNb_units(int nb_units);
            void drawCard();
            void playCard();

            template<typename S>
            void serialisation(S& sa) {
                sa | id_client | nb_units | color | hand;
            }
    };

    template<typename S>
    S& operator|(S& sa, Player& player) {
        player.serialisation(sa);
        return sa;
    }
}
#endif /* ifndef FISK_PLAYER_H */
