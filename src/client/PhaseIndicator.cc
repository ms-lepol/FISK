#include "PhaseIndicator.h"
#include <gf/Color.h>
#include <gf/Font.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <string>


namespace fisk {


    PhaseIndicator::PhaseIndicator(gf::Color4f color, gf::ResourceManager& rm, gf::TextureAtlas& atlas) : 
        ressources(rm), 
        atlas(atlas) {
        //Logic
        this->position = {501,636};
        m_spr.setTexture(atlas.getTexture());
        this->color = color;
        phase = TurnPhase::End;
        }

    void PhaseIndicator::changePhase() {
        phase = static_cast<TurnPhase>((static_cast<int>(phase) + 1) % 4);
    }
    
    void PhaseIndicator::setColor(gf::Color4f color) {
        this->color = color;
    }

    void PhaseIndicator::setPosition(gf::Vector2i position) {
        this->position = position;
    }
    void PhaseIndicator::render(gf::RenderTarget& target,const gf::RenderStates& states){
        gf::RenderStates state;
        //rendering block by block
        m_spr.setPosition(position);

        //rendering background
        for (int i = 0;i<(int)phase;i++) {
            gf::RectangleShape rect({43,11});
            rect.setColor(color);
            rect.setPosition({static_cast<float>(position.x + 83 + i*(rect.getSize().x+5)), static_cast<float>(position.y + 59)});
            m_spr.setPosition(position);
            target.draw(rect, state);
        }
        
       
        //rendering hud
        m_spr.setTexture(atlas.getTexture(),atlas.getTextureRect("hudState"));
        target.draw(m_spr, state);

        //rendering text
        std::string text;
        switch (phase) {
            case TurnPhase::Reinforce:
                text = "Reinforce";
                break;
            case TurnPhase::Attack:
                text = "Attack";
                break;
            case TurnPhase::Fortify:
                text = "Fortify";
                break;
            case TurnPhase::End:
                text = "Waiting";
                break;
            default:
                text = "Error";
                break;

        }
        gf::Font& font = ressources.getFont("font/PixelSplitter-Bold.ttf");
        gf::Text drawn_text(text, font, 25);
        
        drawn_text.setPosition({static_cast<float>(position.x + width/2 - drawn_text.getLocalBounds().getSize().x/2), static_cast<float>(position.y + (height/2))});

        target.draw(drawn_text, state);
        
    }
}