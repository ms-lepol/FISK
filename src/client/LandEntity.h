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
#include <gf/Animation.h>
#include <gf/AnimatedSprite.h>

#include "../common/FiskColors.h"




namespace fisk {
    
    struct GameHub;

    class LandEntity : public gf::Entity {
            
        private:
            
            std::string name;
            gf::Vector2i position;
            gf::Vector2i positionText;
            PlayerId prev_owner;

            GameHub& game_hub;


            gf::Texture& m_texture;
            gf::Animation land_explosion;
            bool changed_owner;
            
            
        public:

            gf::SpriteWidget spr_widg;

            LandEntity(std::string name, std::string sprite_path, gf::Vector2i position,gf::Vector2i positionText, GameHub& gm);
            LandEntity();
            void setNbUnit(unsigned nb_unit);
            
            gf::Color4f getColor();
            std::string getName();

            bool have_owner_changed();

            
            void update(gf::Time time);
            void render(gf::RenderTarget& target, gf::RenderStates states);
            void renderSelected(gf::RenderTarget& target, gf::RenderStates states);
            void renderHinted(gf::RenderTarget& target, gf::RenderStates states);
            void renderAnimation(gf::RenderTarget& target, gf::RenderStates states);
        };
}
#endif // FISK_LAND_ENTITY_H
