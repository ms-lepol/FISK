#ifndef FISK_CARD_ENTITY_H
#define FISK_CARD_ENTITY_H


#include "../common/Card.h"
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/Vector.h>
#include <gf/Widgets.h>
#include <string>

#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <gf/Texture.h>
#include <gf/Entity.h>

#include <gf/ResourceManager.h>
#include <valarray>
#include "../common/Constants.h"
#include <cstddef>
#include <cstdio>
#include <gf/Color.h>
#include <gf/Font.h>
#include <gf/Rect.h>
#include <gf/Shader.h>
#include <gf/Text.h>
#include <gf/Vector.h>
#include <gf/Widgets.h>
#include <gf/Log.h>
#include <string>
#include <gf/Anchor.h>
#include <gf/RenderStates.h>
#include <gf/RenderTarget.h>


#include "../common/FiskColors.h"


#define CARD_WIDTH 158
#define CARD_HEIGHT 223


namespace fisk {
    


    class CardEntity : public gf::Entity {
            
        private:
            
            Card card;
            std::string land_name;
            gf::Vector2i position;
            gf::ResourceManager& ressources;


            gf::Color4f color;
            gf::Sprite spr_type;
            
            bool selected;
            bool is_joker = false;
        public:

            gf::SpriteWidget spr_widg;

            CardEntity(Card card, gf::ResourceManager &rm,std::string land_name = "LandName");
            
            
            void setSelected(bool selected);
            void setPosition(gf::Vector2i position);
            void setPositionText(gf::Vector2i positionText);
            void setCard(Card card);

            Card getCard();
            std::string getLandName();
            void setLandName(std::string land_name);
            gf::Vector2i getPosition();

            bool isSelected();

            void render(gf::RenderTarget& target,const gf::RenderStates& states);

        };
}
#endif // FISK_LAND_ENTITY_H
