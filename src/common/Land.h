#include <string>
#include <vector>

class Land {
    unsigned nb_units;
    std::string name;
    std::vector<unsigned> neighbors;
    unsigned player_id;
};
