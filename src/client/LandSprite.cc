
#include "LandSprite.h"


namespace fisk {

    LandSprite::LandSprite(std::string name, unsigned player_id, gf::Color4f color, std::string sprite_path,gf::Vector2i position) : Land(0, name, std::vector<unsigned>(), player_id) {
        this->nb_units = 0;
        this->name = name;
        this->neighbors = neighbors;
        this->owner_id = player_id;
        //Rendering
        this->color = color;
        this->texture = gf::Texture(sprite_path);
        this->spr.setTexture(texture);
        this->spr.setPosition(position);
    }

    gf::Color4f LandSprite::getColor() {
        return color;
    }

    void LandSprite::setColor(gf::Color4f color) {
        this->color = color;
    }

    void LandSprite::draw(gf::RenderTarget& target) {
        gf::RenderStates state;
        
        target.draw(spr, state);
    }
}