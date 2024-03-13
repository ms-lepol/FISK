#ifndef FISK_END_SCENE_H
#define FISK_END_SCENE_H

#include <gf/Entity.h>
#include <gf/EntityContainer.h>
#include <gf/Scene.h>
#include <gf/Action.h>

#include "HandEntity.h"
#include <gf/RenderWindow.h>
#include <gf/Shapes.h>
#include <gf/Text.h>
#include <gf/Views.h>
#include <gf/TextureAtlas.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>


namespace fisk {

    struct GameHub;


    class EndScene : public gf::Scene {
        public:
            EndScene(GameHub& game);

        private:
            void doHandleActions(gf::Window& window) override;
            void doUpdate(gf::Time time) override;
            void doRender(gf::RenderTarget& target, const gf::RenderStates& states) override;
            void doProcessEvent(gf::Event& event) override;
            void declareWinner(std::string winner);

        private:
            GameHub& m_game;

            
            gf::TextureAtlas e_hudAtlas;

            // containers

            gf::WidgetContainer e_hudButtons;

            gf::RoundedRectangleShape background;
            // entities

           
            // widgets
            gf::SpriteWidget e_closeButton;
            gf::Text e_endText;
            gf::TextButtonWidget e_replayButton;

            // actions

            gf::Action e_interact;
            gf::Action e_close;

            gf::Vector2f mousePos;
            
    };

}

#endif // FISK_CARD_SCENE_H
