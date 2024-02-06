#ifndef FISK_HANDENTITY_H
#define FISK_HANDENTITY_H
#include "CardEntity.h"

#include <gf/Entity.h>
#include <gf/ResourceManager.h>
#include <gf/Vector.h>
#include <vector>
namespace fisk {

    struct GameHub;

    class HandEntity : public gf::Entity{
        private:
            
            gf::ResourceManager& ressources;
            gf::Vector2i position;
            GameHub& game_hub;
            
            gf::Vector2i dimensions;

        public:
            HandEntity(GameHub& gm);

            std::vector<CardEntity> cards;
            void setPosition(gf::Vector2i pos);

            gf::Vector2i getDimensions();

            void render(gf::RenderTarget& target,const gf::RenderStates& states);
            void update(gf::Time time);
    }
;   
}
#endif // FISK_HANDENTITY_H