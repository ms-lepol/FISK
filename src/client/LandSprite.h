#include "../common/Land.h"
#include <gf/Color.h>
#include <gf/Sprite.h>
#include <gf/Vector.h>
#include <string>
#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <gf/Texture.h>
#include <vector>



namespace fisk {
    class LandSprite : private Land{
        private:
            gf::Color4f color;
            gf::Sprite spr;
            gf::Texture texture;
        public:
            LandSprite(std::string name, unsigned player_id, gf::Color4f color, std::string sprite_path,gf::Vector2i position);
            void setColor(gf::Color4f color);
            gf::Color4f getColor();

            void draw(gf::RenderTarget& target);
        };
}
