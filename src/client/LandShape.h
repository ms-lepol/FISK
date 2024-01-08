#include <gf/Color.h>
#include <gf/Polygon.h>
#include <gf/Shapes.h>
#include <gf/Vector.h>
#include <string>
#include <gf/Font.h>
#include <gf/Keyboard.h>
#include <gf/RenderStates.h>
#include <gf/RenderTarget.h>
#include <gf/Text.h>
#include <gf/Vector.h>

#include "../common/Land.h"

namespace fisk {
    class LandShape : private Land {
        private:
            gf::Color4f color;
            gf::Polygon polygon;
            bool selected;

            gf::Vector2i getCenter();
            gf::ConvexShape getShape();
            void blink();


        public:
            LandShape(unsigned nb_units, std::string name, std::vector<unsigned> neighbors, unsigned player_id, gf::Color4f color, gf::Polygon polygon);

            //Getters
           

            //Rendering
            gf::Color4f getColor();
            void setColor(gf::Color4f color);
           
           void draw(gf::RenderTarget& target);
        };

}