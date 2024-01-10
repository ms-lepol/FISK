#include "LandEntity.h"

#include <array>
#include <gf/Array2D.h>
#include <gf/Entity.h>
#include <gf/EntityContainer.h>
#include <memory>
#include <vector>

#include "configMap1.h"

namespace fisk  {
    
    class MapEntity : public gf::Entity {
        private:
            gf::ResourceManager& ressources;

            std::vector<LandEntity*> lands;
            void configureMap1();

       public:
            ~MapEntity();
            MapEntity(gf::ResourceManager& rm , unsigned level_id);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);
            
    };
}