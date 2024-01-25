#ifndef FISK_LOBBY_PLAYER_H
#define FISK_LOBBY_PLAYER_H
#include <gf/Entity.h>
#include <gf/Color.h>
#include <gf/Font.h>
#include <gf/ResourceManager.h>
#include <gf/Sprite.h>
#include <gf/TextureAtlas.h>
#include <gf/Vector.h>
#include <string>
#include <gf/RenderTarget.h>
#include <gf/Shapes.h>

#include "FiskColors.h"

namespace fisk {
    class LobbyPlayer : public gf::Entity {
        static int nextPlot;

        private:
            gf::Vector2i position;
            gf::Vector2i positionName;
            gf::Vector2i positionSprite;
            gf::Color4f color;
            gf::Sprite sprite;
            std::string name;

            gf::Font& font;
            gf::ResourceManager& rm;

            gf::TextureAtlas l_hudAtlas;

            bool plotIsFilled;
            bool isReady;
        public:
            LobbyPlayer(gf::ResourceManager& rm);
            void render(gf::RenderTarget& target, const gf::RenderStates& states) override;
            void update(gf::Time time) override;
    };
}
#endif // FISK_LOBBY_PLAYER_H