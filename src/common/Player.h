#include <gf/Color.h>
namespace fisk {
    class Player {
        private:
            int id_client;
            int nb_units;
            gf::Color4f color;
            int hand[];
        public:
            Player(int id_client, int nb_units, gf::Color4f color, int hand[]);
            int getId_client();
            int getNb_units();
            gf::Color4f getColor();
            void setNb_units(int nb_units);
            void drawCard();
            void playCard();
    };
}