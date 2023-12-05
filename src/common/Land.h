#include <string>
#include <vector>

namespace fisk {

    class Land {
        unsigned nb_units;
        std::string name;
        std::vector<unsigned> neighbors;
        unsigned player_id;
    };
}
