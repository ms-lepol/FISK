#include "LandEntity.h"

#include <gf/Array2D.h>
#include <gf/Entity.h>

#include "configMap1.h"

namespace fisk  {
    class MapEntity : public gf::Entity {
        private:
            gf::ResourceManager& ressources;
            LandEntity map;
            void configureMap1();
        public:
            MapEntity(gf::ResourceManager& rm , unsigned level_id);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);
            
    };
}