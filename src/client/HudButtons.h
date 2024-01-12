#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Widgets.h>
#include <gf/WidgetContainer.h>
#include <gf/TextureAtlas.h>
#include <gf/Log.h>
#include <gf/RenderTarget.h>
#include <gf/Vector.h>

namespace fisk {
    class HudButtons : public gf::Entity{
        
        private:
            gf::WidgetContainer widg_container;


            gf::SpriteWidget widg_quit;
            gf::SpriteWidget widg_card;
            gf::SpriteWidget widg_help;
            gf::SpriteWidget widg_settings;

            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;
            

            void callbackCardButton();

        public:
            int size = 64;

            HudButtons(gf::ResourceManager& rm, gf::TextureAtlas& atlas);

            void render(gf::RenderTarget& target, const gf::RenderStates& states);

    };

}