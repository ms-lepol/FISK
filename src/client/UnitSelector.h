#ifndef FISK_UNITSELECTOR_H
#define FISK_UNITSELECTOR_H

#include <gf/ResourceManager.h>
#include <gf/WidgetContainer.h>
#include <gf/Widgets.h>
#include "../common/FiskColors.h"
#include "../common/Land.h"
#include <gf/Entity.h>
#include <gf/RenderTarget.h>
#include <gf/RenderStates.h>
#include <gf/Vector.h>
#include <gf/Time.h>
#include <gf/Log.h>
#include <gf/Text.h>

namespace fisk {

    struct GameHub; 

    class UnitSelector : public gf::Entity {
    public:
        UnitSelector(GameHub& game);
        void update(gf::Time time);
        void render(gf::RenderTarget& target, const gf::RenderStates& states);
        void setPosition(gf::Vector2i pos);
        gf::Vector2i getDimensions();
        void setMaxUnit(Land& land_clicked);
    private:
        GameHub& game_hub;
        gf::ResourceManager& ressources;

        //Rendering
        gf::Vector2i position;
        gf::Vector2i dimensions;

        //Widgets
        gf::WidgetContainer s_container;
        gf::TextButtonWidget s_left;
        gf::TextButtonWidget s_right;
        gf::TextButtonWidget s_validate;
        gf::TextButtonWidget s_cancel;

        //Logic
        int selected_unit;
        int max_unit;


    };


}
#endif //FISK_UNITSELECTOR_H