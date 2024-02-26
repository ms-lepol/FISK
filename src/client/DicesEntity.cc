#include "DicesEntity.h"
#include <gf/Log.h>
#include <gf/Sleep.h>
#include <gf/Time.h>

#define STEP 144


namespace fisk {

    
    static constexpr gf::Vector2i dices_attacker_mov = {1, 0};
    static constexpr gf::Vector2i dices_defender_mov = {-1, 0};

    static constexpr gf::Vector2i dices_scale = {4, 4};

    DicesEntity::DicesEntity(gf::ResourceManager& rm, gf::TextureAtlas& atlas, GameHub& game)
    : m_game(game)
    , ressources(rm)
    , atlas(atlas)
    {
        initTextures();
    }

    void DicesEntity::initTextures() {
        atlas.setTexture(ressources.getTexture("sprites/dices.png"));
        dices_attacker_1.setTexture(atlas.getTexture());
        dices_attacker_1.setScale(dices_scale);
        dices_attacker_2.setTexture(atlas.getTexture());
        dices_attacker_2.setScale(dices_scale);
        dices_attacker_3.setTexture(atlas.getTexture());
        dices_attacker_3.setScale(dices_scale);

        dices_defender_1.setTexture(atlas.getTexture());
        dices_defender_1.setScale(dices_scale);
        dices_defender_2.setTexture(atlas.getTexture());
        dices_defender_2.setScale(dices_scale);
        dices_defender_3.setTexture(atlas.getTexture());
        dices_defender_3.setScale(dices_scale);

    }

    void DicesEntity::setDices(std::vector<int> attacker, std::vector<int> defender) {
        dices_attacker = attacker;
        dices_defender = defender;
    }

    std::string get_dice_texture_name_by_value(int value , bool attacker){
        std::string texture_name = "";
        if(attacker){
            texture_name += "white_";
        } else {
            texture_name += "red_";
        }
        texture_name += "dice_";
        texture_name += std::to_string(value);
        return texture_name;
    }

    void DicesEntity::launchDices() {
        if (!dices_attacker.empty() && !dices_defender.empty()){
            launched = true;
            dices_attacker_1.setPosition({0,STEP});
            dices_attacker_2.setPosition({0,STEP*2});
            dices_attacker_3.setPosition({0,STEP*3});
            
            dices_defender_1.setPosition({1280,STEP});
            dices_defender_2.setPosition({1280,STEP*2});
            dices_defender_3.setPosition({1280,STEP*3});

            for (int i = 0; i < dices_attacker.size(); i++) {
                if (i == 0) dices_attacker_1.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_attacker[i], true)));
                if (i == 1) dices_attacker_2.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_attacker[i], true)));
                if (i == 2) dices_attacker_3.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_attacker[i], true)));
            }

            for (int i = 0; i < dices_defender.size(); i++) {
                if (i == 0) dices_defender_1.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_defender[i], false)));
                if (i == 1) dices_defender_2.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_defender[i], false)));
                if (i == 2) dices_defender_3.setTextureRect(atlas.getTextureRect(get_dice_texture_name_by_value(dices_defender[i], false)));
            }
         }

    }

    void DicesEntity::update(gf::Time time) {
        if (launched) {
            if (dices_speed > 50 ) dices_speed -=10;
            dices_attacker_1.move(dices_attacker_mov * dices_speed * time.asSeconds());
            dices_attacker_2.move(dices_attacker_mov * dices_speed * time.asSeconds());
            dices_attacker_3.move(dices_attacker_mov * dices_speed * time.asSeconds());

            dices_defender_1.move(dices_defender_mov * dices_speed * time.asSeconds());
            dices_defender_2.move(dices_defender_mov * dices_speed * time.asSeconds());
            dices_defender_3.move(dices_defender_mov * dices_speed * time.asSeconds());

            if (dices_speed <= 50) {
                gf::sleep(gf::Time(std::chrono::milliseconds(2000)));
                launched = false;
                dices_speed = 500.0f;
            }
        }
    }

    void DicesEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        if (launched) {
            if (!dices_attacker.empty() && !dices_defender.empty()){
                if (dices_attacker.size() >= 1) target.draw(dices_attacker_1, states);
                if (dices_attacker.size() >= 2) target.draw(dices_attacker_2, states);
                if (dices_attacker.size() >= 3) target.draw(dices_attacker_3, states);  

                if (dices_defender.size() >= 1) target.draw(dices_defender_1, states);
                if (dices_defender.size() >= 2) target.draw(dices_defender_2, states);
                if (dices_defender.size() >= 3) target.draw(dices_defender_3, states);
            }
        }
    }

}