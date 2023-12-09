#include <gf/Color.h>
#include <gf/Polygon.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <string>
#include "../common/Land.h"

namespace fisk {
    class LandShape : private Land {
        private:
            gf::Color4f color;
            gf::Polygon polygon;
        public:
            LandShape(unsigned nb_units, std::string name, std::vector<unsigned> neighbors, unsigned player_id, gf::Color4f color, gf::Polygon polygon);
            //Rendering
            gf::Color4f getColor();
            void setColor(gf::Color4f color);
            gf::ConvexShape getShape();
        };

}