#ifndef FISK_LAND_ENTITY_H
#define FISK_LAND_ENTITY_H


#include "../common/Land.h"
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
    


    class LandEntity : public gf::Entity {
            
        private:
            
            Land land;
            gf::Vector2i position;
            gf::Vector2i positionText;

            gf::ResourceManager& ressources;


            gf::Color4f color;
            
            gf::Texture& m_texture;
            bool selected;
        public:

            gf::SpriteWidget spr_widg;

            LandEntity(std::string name, PlayerId player_id, std::string sprite_path, gf::Vector2i position,gf::Vector2i positionText, gf::ResourceManager &rm);
            LandEntity();
            void setColor(gf::Color4f color);
            bool isSelected();
            gf::Color4f getColor();

            void render(gf::RenderTarget& target, gf::RenderStates states);
            void renderSelected(gf::RenderTarget& target, gf::RenderStates states);

        };
}
#endif // FISK_LAND_ENTITY_H
