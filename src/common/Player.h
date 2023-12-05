#include <gf/Color.h>
#include <vector>
namespace fisk {
    class Player {
        private:
            unsigned id_client;
            unsigned nb_units;
            gf::Color4f color;
            std::vector<unsigned> hand;
        public:
            Player(int id_client, int nb_units, gf::Color4f color, std::vector<unsigned> hand);
            Player(int id_client, int nb_units, gf::Color4f color, unsigned card...);
            int getId_client();
            int getNb_units();
            gf::Color4f getColor();
            void setNb_units(int nb_units);
            void drawCard();
            void playCard();
    };
}
