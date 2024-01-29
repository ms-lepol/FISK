#ifndef FISK_PHASE_INDICATOR_H
#define FISK_PHASE_INDICATOR_H value
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

#include "../common/Enums.h"

#define texture_path "/sprites/fisk_ui.png"

namespace fisk {
    class PhaseIndicator : public gf::Entity {
        private:
            TurnPhase phase = TurnPhase::End;
            gf::Sprite m_spr;
            gf::Vector2i position;
            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;
            gf::Color4f color;
        public:
            int width = 304;
            int height = 80;
            PhaseIndicator(gf::Color4f color, gf::ResourceManager& rm, gf::TextureAtlas& atlas);
            void changePhase();
            void render(gf::RenderTarget& target,const gf::RenderStates& states);
            void setPosition(gf::Vector2i position);
            void setColor(gf::Color4f color);
        };

}
#endif /* ifndef FISK_PHASE_INDICATOR_H */
