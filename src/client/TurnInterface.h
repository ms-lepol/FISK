#ifndef FISK_TURN_INTERFACE_H
#define FISK_TURN_INTERFACE_H value
#include <gf/Color.h>
#include <gf/Entity.h>
#include <gf/Polygon.h>
#include <gf/Shape.h>
#include <gf/Shapes.h>
#include <gf/Sprite.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <string>
#include "../common/FiskColors.h"
#include <gf/ResourceManager.h>
#include <gf/RenderTarget.h>

#define x_PosTI 1382
#define y_PosTI 217

#define texture_path "/sprites/fisk_ui.png"

namespace fisk {

    struct GameHub;
    class TurnInterface : public gf::Entity {
        private:
            GameHub& m_game;
            unsigned nb_player;
            unsigned turn_order;
            gf::Sprite m_spr;
            gf::Vector2i position;
            gf::Vector2i text_position;
            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;
        public:
            int width = 96;
            int height = 72;
            TurnInterface(GameHub& game, gf::ResourceManager& rm, gf::TextureAtlas& atlas);
            void setNbPlayer(unsigned nb_player);
            void setTurnOrder(gf::Color4f color);
            void changeTurn();
            void update();
            void render(gf::RenderTarget& target,const gf::RenderStates& states);
            void setPosition(gf::Vector2i position);
        };

}
#endif /* ifndef FISK_TURN_INTERFACE_H */
