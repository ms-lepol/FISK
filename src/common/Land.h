#include <string>
#include <vector>

class Land {
    private:
        unsigned land_id;
        unsigned nb_units;
        std::string name;
        std::vector<unsigned> neighbors;
        unsigned owner_id;
    public:
        Land(unsigned nb_units, std::string name, std::vector<unsigned> neighbors, unsigned player_id);
        unsigned getNb_units();
        std::string getName();
        std::vector<unsigned> getNeighbors();
        unsigned getPlayer_id();
        void setOwner_id(unsigned player_id);
        void addNeighbor(unsigned neighbor);
        void removeNeighbor(unsigned neighbor);
        //Actions of the player
        void reinforce(unsigned nb_units);
        void attack(unsigned land_id);
        void fortify(unsigned land_id);
};
