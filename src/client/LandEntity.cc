#include "LandEntity.h"
#include <gf/Vector.h>

namespace fisk {
    LandColor::LandColor(){
        Blue = gf::Color4f({(float)99/255,(float)155/255,(float)255/255,1});
        Orange = gf::Color4f({(float)255/255,(float)140/255,(float)92/255,1});
        Green = gf::Color4f({(float)134/255,(float)192/255,(float)108/255,1});
        Yellow = gf::Color4f({(float)251/255,(float)239/255,(float)8/255,1});
        Neutral = gf::Color4f({(float)48/255,(float)104/255,(float)80/255,1});
    }

    LandEntity::LandEntity(std::string name, PlayerId player_id, std::string sprite_path,gf::Vector2i position,gf::Vector2i positionText,gf::ResourceManager& rm) : 
        land(0, name, std::vector<LandId>(), player_id),
        ressources(rm),
        m_texture(ressources.getTexture(sprite_path)),
        position(position),
        positionText(positionText),
        spr_widg(gf::SpriteWidget())
        {
        //Logic
        
        //Rendering
        spr_widg.setDefaultSprite(m_texture, gf::RectF::fromMinMax({0,0}, {1,1}));
        spr_widg.setPosition(position);
        spr_widg.setCallback([this] {
            gf::Log::info("LandEntity %s : clicked\n", land.getName().c_str());
        });

        this->color = LandColor().Neutral;

      
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
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText);
        target.draw(txt);
    }
}
