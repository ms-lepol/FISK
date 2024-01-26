#include "LandEntity.h"


#define textOffset 1
#define landOutline 50


namespace fisk {
   

    LandEntity::LandEntity(std::string name, PlayerId player_id, std::string sprite_path,gf::Vector2i position,gf::Vector2i positionText,gf::ResourceManager& rm) : 
        land(1, name, std::vector<LandId>(), player_id),
        ressources(rm),
        m_texture(ressources.getTexture(sprite_path)),
        position(position),
        positionText(positionText),
        spr_widg(gf::SpriteWidget())
        {
        //Logic
        selected = false;
        //Rendering
        spr_widg.setDefaultSprite(m_texture, gf::RectF::fromMinMax({0,0}, {1,1}));
        spr_widg.setPosition(position);
        spr_widg.setCallback([this] {
            gf::Log::info("LandEntity %s : clicked\n", land.getName().c_str());
            selected = !selected;
        });

        this->color = LandColor().Neutral;

      
    }

    gf::Color4f LandEntity::getColor() {
        return color;
    }

    void LandEntity::setColor(gf::Color4f color) {
        this->color = color;
    }
    bool LandEntity::isSelected(){
        return selected;
    }

    void LandEntity::render(gf::RenderTarget& target,gf::RenderStates states) {
        
        if (color!=gf::Color::Transparent){
            spr_widg.setColor(color);
        }
        
        target.draw(spr_widg, states);
        gf::Font& font = ressources.getFont("font/PixelSplitter-Bold.ttf");
        std::string text = std::to_string(land.getNb_units());
        if (land.getNb_units() < 10) text = "0" + text;
        gf::Text txt(text, font, 10);
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText+gf::Vector2i({0,1}));
        target.draw(txt,states);
    }


    //Draw an outline if selected
    void LandEntity::renderSelected(gf::RenderTarget& target, gf::RenderStates states){
        if (selected){
            gf::Color4f color;

            if (this->color==LandColor().Neutral){
                color = LandColor().DarkNeutral;
            }
            if (this->color==LandColor().Orange){
                color = LandColor().DarkOrange;
                
            }
            if (this->color==LandColor().Blue){
                color = LandColor().DarkBlue;
                
            }
            if (this->color==LandColor().Green){
                color = LandColor().DarkGreen;
                
            }
            if (this->color==LandColor().Yellow){
                color = LandColor().DarkYellow;
                
            }
            spr_widg.setColor(color);
        }
        target.draw(spr_widg, states);
        gf::Font& font = ressources.getFont("font/PixelSplitter-Bold.ttf");
        std::string text = std::to_string(land.getNb_units());
        if (land.getNb_units() < 10) text = "0" + text;
        gf::Text txt(text, font, 10);
        txt.setAnchor(gf::Anchor::Center);
        txt.setPosition(position+positionText+gf::Vector2i({0,1}));
        target.draw(txt,states);
    }
}
