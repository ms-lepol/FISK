#include "CardScene.h"
#ifndef FISK_HUD_BUTTONS_H
#define FISK_HUD_BUTTONS_H value

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Widgets.h>
#include <gf/WidgetContainer.h>
#include <gf/TextureAtlas.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Vector.h>



namespace fisk {

    struct GameHub;

    class HudButtons : public gf::Entity {
        
        private:
            GameHub& m_game;


            gf::SpriteWidget widg_quit;
            gf::SpriteWidget widg_card;
            gf::SpriteWidget widg_help;
            gf::SpriteWidget widg_settings;
            gf::TextButtonWidget widg_endPhase;

            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;
           

            void callbackCardButton();

        public:
            gf::WidgetContainer widg_container;
            int size = 64;
            void initTextures();
            void placeCardButton(gf::Vector2i position);
            void placeEndPhaseButton(gf::Vector2i position);

            HudButtons(gf::ResourceManager& rm, gf::TextureAtlas& atlas, GameHub& game);

            void update(gf::Time time);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);

    };

}

#endif /* ifndef FISK_HUD_BUTTONS_H */