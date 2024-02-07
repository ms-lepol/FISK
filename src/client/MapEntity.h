#include "CardScene.h"
#ifndef FISK_MAP_ENTITY_H
#define FISK_MAP_ENTITY_H value
#include "LandEntity.h"
#include <gf/WidgetContainer.h>
#include <array>
#include <gf/Array2D.h>
#include <gf/Entity.h>
#include <gf/EntityContainer.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "configMap1.h"

namespace fisk  {

    class MapEntity : public gf::Entity {
        private:
            GameHub& game_hub;

            std::map<std::string, std::unique_ptr<LandEntity>> lands;
            void configureMap1();

       public:

            LandEntity* old_selection;
            LandEntity* curr_selection;

            void select(LandEntity* e);
            void reset_selections();

            gf::WidgetContainer widg_container;
            
            MapEntity(GameHub& gm , unsigned level_id);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);

    };
}
#endif /* ifndef FISK_MAP_ENTITY_H */
