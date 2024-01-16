#include "LandEntity.h"
#include "../common/Constants.h"
#include <cstddef>
#include <gf/Rect.h>
#include <gf/Widgets.h>
#include <gf/Log.h>

namespace fisk {



    LandEntity::LandEntity(std::string name, PlayerId player_id, std::string sprite_path,gf::Vector2i position,gf::ResourceManager& rm) : 
        land(0, name, std::vector<LandId>(), player_id),
        ressources(rm),
        m_texture(ressources.getTexture(sprite_path)),
        position(position),
        spr_widg(gf::SpriteWidget())
        {
        //Logic

        //Rendering
        spr_widg.setDefaultSprite(m_texture, gf::RectF::fromMinMax({0,0}, {1,1}));
        spr_widg.setPosition(position);
        spr_widg.setCallback([this] {
            gf::Log::info("LandEntity %s : clicked\n", land.getName().c_str());
        });

        this->color = gf::Color::Transparent;

      
    }

    gf::Color4f LandEntity::getColor() {
        return color;
    }

    void LandEntity::setColor(gf::Color4f color) {
        this->color = color;
    }

    void LandEntity::render(gf::RenderTarget& target) {
        gf::RenderStates state;
        target.draw(spr_widg, state);
    }
}
