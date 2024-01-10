#ifndef FISK_LAND_ENTITY_H
#define FISK_LAND_ENTITY_H


#include "../common/Land.h"
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/Vector.h>
#include <string>

#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <gf/Texture.h>
#include <gf/Entity.h>

#include <gf/ResourceManager.h>
#include <valarray>

namespace fisk {
    class LandEntity : public gf::Entity {
            
        private:
            
            Land land;
            gf::Vector2i position;

            gf::ResourceManager& ressources;


            gf::Color4f color;
            gf::Sprite spr;
            gf::Texture& m_texture;
            
        public:
            LandEntity(std::string name, unsigned player_id, std::string sprite_path, gf::Vector2i position, gf::ResourceManager &rm);
            LandEntity();
            void setColor(gf::Color4f color);
            gf::Color4f getColor();

            void render(gf::RenderTarget& target);

        };
}
#endif // FISK_LAND_ENTITY_H
