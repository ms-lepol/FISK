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
            gf::ResourceManager& ressources;

            std::map<std::string, std::unique_ptr<LandEntity>> lands;
            void configureMap1();

       public:

            gf::WidgetContainer widg_container;
            
            MapEntity(gf::ResourceManager& rm , unsigned level_id);
            void changeLandColor(std::string land_name, gf::Color4f color);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);

    };
}
#endif /* ifndef FISK_MAP_ENTITY_H */
