#include "LandShape.h"
#include <gf/Keyboard.h>
#include <gf/Vector.h>

namespace fisk {
    LandShape::LandShape(unsigned nb_units, std::string name, std::vector<unsigned> neighbors, unsigned player_id, gf::Color4f color, gf::Polygon polygon) : Land(nb_units, name, neighbors, player_id) {
        this->nb_units = nb_units;
        this->name = name;
        this->neighbors = neighbors;
        this->owner_id = player_id;
        //Rendering
        this->color = color;
        this->polygon = polygon;
    }

    gf::Color4f LandShape::getColor() {
        return color;
    }

    gf::ConvexShape LandShape::getShape() {
        gf::ConvexShape shape = gf::ConvexShape(this->polygon);
        shape.setColor(color);
        return shape;
    }

}