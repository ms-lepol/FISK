#ifndef  FISK_CARD_SCENE_H
#define FISK_CARD_SCENE_H

#include <gf/Entity.h>
#include <gf/EntityContainer.h>
#include <gf/Scene.h>
#include <gf/Action.h>

#include "HandEntity.h"
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>


namespace fisk {

    struct GameHub;

    struct hudEntity : gf::Entity {
        gf::WidgetContainer c_hudButtons;

        hudEntity(gf::WidgetContainer& hudButtons) : c_hudButtons(hudButtons) {
        
        }
        void render(gf::RenderTarget& target, const gf::RenderStates& states) override {
            c_hudButtons.render(target, states);
        }
    };

    class CardScene : public gf::Scene {
        public:
            CardScene(GameHub& game);

        private:
            void doHandleActions(gf::Window& window) override;
            void doUpdate(gf::Time time) override;
            void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;
            void doProcessEvent(gf::Event& event) override;

        private:
            GameHub& m_game;

            
            gf::TextureAtlas c_hudAtlas;

            // containers

            gf::WidgetContainer c_hudButtons;

            gf::RoundedRectangleShape background;
            // entities

            HandEntity c_handEntity;

            // widgets
            gf::SpriteWidget c_closeButton;
            gf::TextButtonWidget c_playCard;

            // actions

            gf::Action c_interact;
            gf::Action c_close;

            gf::Vector2f mousePos;
            hudEntity c_hudEntity;
    };

}

#endif // FISK_CARD_SCENE_H
