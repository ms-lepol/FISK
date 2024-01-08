#include "LandShape.h"
#include <gf/Shapes.h>
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
        this->selected = false;
    }

    gf::Color4f LandShape::getColor() {
        return color;
    }

    gf::ConvexShape LandShape::getShape() {
        gf::ConvexShape shape = gf::ConvexShape(this->polygon);
        shape.setColor(color);
        return shape;
    }

    gf::Vector2i LandShape::getCenter() {
        return polygon.getCenter();
    }

    void LandShape::blink() {
        this->selected = !this->selected;
    }

    void LandShape::setColor(gf::Color4f color) {
        this->color = color;
    }

    void LandShape::draw(gf::RenderTarget& target) {
        gf::RenderStates states = gf::RenderStates();
        gf::ConvexShape shape = gf::ConvexShape(this->polygon);
        shape.setColor(color);
        target.draw(shape, states);

        if (selected) {
            gf::ConvexShape shape = gf::ConvexShape(this->polygon);
            shape.setColor(gf::Color::fromRgba32(0, 0, 0, 0));
            shape.setOutlineColor(gf::Color::fromRgba32(0, 0, 0, 255));
            shape.setOutlineThickness(5);
            target.draw(shape, states);
        }
    
        gf::Font font("../data/font/Kaph-Regular.ttf");
       
        gf::Vector2i center = this->getCenter();

        gf::CircleShape circle(30);
        circle.setPosition(center-gf::Vector2i(30,30));
        circle.setColor(gf::Color::fromRgba32(0, 0, 0, 0));
        circle.setOutlineColor(gf::Color::fromRgba32(0, 0, 0, 255));
        circle.setOutlineThickness(5);
        target.draw(circle, states);


        char textstr[10];
        sprintf(textstr, "%d", this->nb_units);

        gf::Text text(textstr, font, 50);
        
        text.setPosition(circle.getPosition() + gf::Vector2f(10,50));
        text.setColor(gf::Color::Black);

        target.draw(text, states);

    }

}
