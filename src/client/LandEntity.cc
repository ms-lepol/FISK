#include "LandEntity.h"
#include "../common/Constants.h"
#include <cstddef>
#include <cstdio>
#include <gf/Color.h>
#include <gf/Font.h>
#include <gf/Rect.h>
#include <gf/Shader.h>
#include <gf/Text.h>
#include <gf/Widgets.h>
#include <gf/Log.h>
#include <string>

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

        this->color = gf::Color::Red;

      
    }

    gf::Color4f LandEntity::getColor() {
        return color;
    }

    void LandEntity::setColor(gf::Color4f color) {
        this->color = color;
    }

    void LandEntity::render(gf::RenderTarget& target) {
        gf::RenderStates state;

        if (color!=gf::Color::Transparent){
            spr_widg.setColor(color);
        }
        
        target.draw(spr_widg, state);
        gf::Font& font = ressources.getFont("font/PixelSplitter-Bold.ttf");
        std::string text = std::to_string(land.getNb_units());
        gf::Text txt(text, font, 15);
        txt.setPosition(position+gf::Vector2i(10,10));
        target.draw(txt);
    }
}
