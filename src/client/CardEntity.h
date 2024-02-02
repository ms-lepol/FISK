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



namespace fisk {
    


    class CardEntity : public gf::Entity {
            
        private:
            
            Card card;
            std::string land_name;
            gf::Vector2i position;
            gf::Vector2i positionText;

            gf::ResourceManager& ressources;


            gf::Color4f color;
            gf::Sprite spr_type;
            
            bool selected;
        public:

            gf::SpriteWidget spr_widg;

            CardEntity(CardId card_id, PlayerId player_id, gf::ResourceManager &rm);
            CardEntity();
            bool isSelected();

            void render(gf::RenderTarget& target, gf::RenderStates states);

        };
}
#endif // FISK_LAND_ENTITY_H
