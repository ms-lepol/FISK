#include "CardEntity.h"

#include <gf/Anchor.h>
#include <gf/RenderTarget.h>

namespace fisk {
    
        CardEntity::CardEntity(Card card, gf::ResourceManager& rm,std::string land_name)
        : land_name(land_name)
        , selected(false)
        , ressources(rm)
        , card(card)
        {
            spr_widg.setDefaultSprite(ressources.getTexture("sprites/cards/cardbg.png"), gf::RectF::fromMinMax({0,0}, {1,1}));
            spr_widg.setPosition(position);
            spr_widg.setCallback([this] {
                gf::Log::info("CardEntity %s : clicked\n", this->land_name.c_str());
                selected = !selected;
            });


            switch(card.getType()) {
                case Type::Gunner:
                    spr_type.setTexture(ressources.getTexture("sprites/cards/tank.png"));
                    break;
                case Type::Infantery:
                    spr_type.setTexture(ressources.getTexture("sprites/cards/infantery.png"));
                    break;
                case Type::Cavalry:
                    spr_type.setTexture(ressources.getTexture("sprites/cards/horse.png"));
                    break;
                case Type::Joker:
                    is_joker = true;
                    break;
            }
            
        }
    
        void CardEntity::render(gf::RenderTarget& target,const gf::RenderStates& states) {
            target.draw(spr_widg, states);
            gf::Font& font = ressources.getFont("font/PixelSplitter-Bold.ttf");
            if(!is_joker) {
                spr_type.setAnchor(gf::Anchor::Center);
                spr_type.setPosition(position + gf::Vector2f({CARD_WIDTH/2, CARD_HEIGHT/4}));
                target.draw(spr_type, states);
            } else {
                
                gf::Text txt("?", font, 40);
                txt.setAnchor(gf::Anchor::Center);
                txt.setPosition(position + gf::Vector2f({CARD_WIDTH/2, CARD_HEIGHT/2}));
                txt.setColor(HUDColor().buttonColor);
                target.draw(txt, states);
            }

            gf::Text land_txt(land_name, font, 10);
            land_txt.setAnchor(gf::Anchor::Center);
            land_txt.setPosition(position + gf::Vector2f({CARD_WIDTH/2, CARD_HEIGHT/2 + 20}));
            land_txt.setColor(HUDColor().buttonColor);
            target.draw(land_txt, states);


        }
    
      
        bool CardEntity::isSelected() {
            return selected;
        }
    
        Card CardEntity::getCard() {
            return card;
        }
    
        std::string CardEntity::getLandName() {
            return land_name;
        }
    
        void CardEntity::setLandName(std::string land_name) {
            this->land_name = land_name;
        }

        gf::Vector2i CardEntity::getPosition() {
            return position;
        }
    
    
        void CardEntity::setSelected(bool selected) {
            this->selected = selected;
        }
    
        void CardEntity::setPosition(gf::Vector2i position) {
            this->position = position;
            spr_widg.setPosition(position);
        }
    
        
    
}