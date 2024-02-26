
#include <gf/Sprite.h>
#ifndef FISK_DICE_ENTITY_H
#define FISK_DICE_ENTITY_H value

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

    class DicesEntity : public gf::Entity {
        
        private:
            GameHub& m_game;


            std::vector<int> dices_attacker;
            std::vector<int> dices_defender;

            gf::ResourceManager& ressources;
            gf::TextureAtlas& atlas;

            gf::Sprite dices_attacker_1;
            gf::Sprite dices_attacker_2;
            gf::Sprite dices_attacker_3;

            gf::Sprite dices_defender_1;
            gf::Sprite dices_defender_2;
            gf::Sprite dices_defender_3;

            float dices_speed = 500.0f;
           
            bool launched = false;

        public:
            
            int size = 64;
            void initTextures();
            void setDices(std::vector<int> attacker, std::vector<int> defender);
            void launchDices();

            DicesEntity(gf::ResourceManager& rm, gf::TextureAtlas& atlas, GameHub& game);

            void update(gf::Time time);
            void render(gf::RenderTarget& target, const gf::RenderStates& states);

    };

}

#endif /* ifndef FISK_DICES_ENTITY_H */