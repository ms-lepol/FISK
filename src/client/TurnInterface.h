#include <gf/Color.h>
#include <gf/Entity.h>
#include <gf/Polygon.h>
#include <gf/Shape.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <string>
#include <gf/ResourceManager.h>
#include <gf/RenderTarget.h>

#define x_PosTI 1382
#define y_PosTI 217

#define texture_path "/sprites/fisk_ui.png"
#define texture_witdh 576
#define texture_height 208

namespace fisk {
    class TurnInterface : public gf::Entity {
        private:
            unsigned nb_player;
            unsigned turn_order;
            gf::Sprite m_spr;
            gf::Vector2i position;
            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;
        public:
            int width = 96;
            TurnInterface(unsigned nb_player, gf::ResourceManager& rm, gf::TextureAtlas& atlas);
            void changeTurn();
            void render(gf::RenderTarget& target,const gf::RenderStates& states);
            void setPosition(gf::Vector2i position);
        };

}
