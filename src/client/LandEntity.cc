
#include "LandEntity.h"

namespace fisk {

    

    LandEntity::LandEntity(std::string name, unsigned player_id, std::string sprite_path,gf::Vector2i position,gf::ResourceManager& rm) : 
        land(0, name, std::vector<unsigned>(), player_id),
        ressources(rm),
        m_texture(ressources.getTexture(sprite_path)),
        position(position)
        {
        //Logic
        
        //Rendering
        this->color = gf::Color::Transparent;

        this->spr.setTexture(m_texture);
        this->spr.setPosition(this->position);
    }

    gf::Color4f LandEntity::getColor() {
        return color;
    }

    void LandEntity::setColor(gf::Color4f color) {
        this->color = color;
    }

    void LandEntity::render(gf::RenderTarget& target) {
        gf::RenderStates state;
        
        target.draw(spr, state);
    }
}