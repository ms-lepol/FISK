#include "UnitSelector.h"
#include <gf/Alignment.h>
#include <gf/Anchor.h>
#include <gf/Shapes.h>
#include <string>

#include "GameHub.h"


#define font "font/PixelSplitter-Bold.ttf"

namespace fisk {
    UnitSelector::UnitSelector(GameHub& game): game_hub(game)
                                               ,ressources(game.resources) 
                                               ,s_left("<",ressources.getFont(font),20)
                                               ,s_right(">",ressources.getFont(font),20)
                                               ,s_validate("Validate",ressources.getFont(font),20)
                                               ,s_cancel("Cancel",ressources.getFont(font),20){
        position = {0, 0};
        dimensions = {250, 100};
        
        max_unit = 10;
        min_unit = 1;
        selected_unit = min_unit;
        s_container.addWidget(s_left);
        s_container.addWidget(s_right);
        s_container.addWidget(s_validate);
        s_container.addWidget(s_cancel);

        s_left.setPosition(position + gf::Vector2i({dimensions.x/4, dimensions.y/2}));
        s_right.setPosition(position + gf::Vector2i({3*dimensions.x/4, dimensions.y/2}));
        s_validate.setPosition(position + gf::Vector2i({dimensions.x/4, 3*dimensions.y/4}));
        s_cancel.setPosition(position + gf::Vector2i({3*dimensions.x/4, 3*dimensions.y/4}));

        s_left.setPadding(5);
        s_right.setPadding(5);
        s_validate.setPadding(5);
        s_cancel.setPadding(5);

        s_left.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_right.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_validate.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_cancel.setDefaultBackgroundColor(HUDColor().buttonColor);

        s_left.setDefaultTextColor(HUDColor().backgroundColor);
        s_right.setDefaultTextColor(HUDColor().backgroundColor);
        s_validate.setDefaultTextColor(HUDColor().backgroundColor);
        s_cancel.setDefaultTextColor(HUDColor().backgroundColor);

        

        s_validate.setAnchor(gf::Anchor::Center);
        s_cancel.setAnchor(gf::Anchor::Center);
        s_left.setAnchor(gf::Anchor::Center);
        s_right.setAnchor(gf::Anchor::Center);

    }

    void UnitSelector::setPosition(gf::Vector2i pos) {
        position = pos;
        s_left.setPosition(position + gf::Vector2i({dimensions.x/4, dimensions.y/2}));
        s_right.setPosition(position + gf::Vector2i({3*dimensions.x/4, dimensions.y/2}));
        s_validate.setPosition(position + gf::Vector2i({dimensions.x/4, 3*dimensions.y/4}));
        s_cancel.setPosition(position + gf::Vector2i({3*dimensions.x/4, 3*dimensions.y/4}));

    }

    gf::Vector2i UnitSelector::getDimensions() {
        return dimensions;
    }

    void UnitSelector::update(gf::Time time) {
        if (hidden) return;
        auto& map = game_hub.mainScene.m_map;
        auto& model = game_hub.clientNetwork.getGameModel();
        switch (model.get_current_phase()) {
            case TurnPhase::Fortify:
                setMaxUnit(model.get_player(game_hub.clientNetwork.getClientId()).getNb_units()+1);
                break;
            case TurnPhase::Attack:
                if (map.old_selection != nullptr) {
                    int units = model.get_land_by_name(map.old_selection->getName()).getNb_units();
                    int n = 4;
                    if(units <= 4) n = units;
                    if(n <= 1) n = 1;
                    setMaxUnit(n);
                }
                break;
            case TurnPhase::Reinforce:        
                if (map.old_selection != nullptr && map.curr_selection != nullptr) {
                    setMaxUnit(model.get_land_by_name(map.old_selection->getName()).getNb_units());
                }
            break;
            case TurnPhase::End:
                break;

        }
        
        
    }

    void UnitSelector::setCallbacks(){
        s_left.setCallback([this](){
            gf::Log::debug("Max unit : %d\n", max_unit);
            selected_unit = (selected_unit-1 < min_unit) ? max_unit-1 : selected_unit-1;
        });
        s_right.setCallback([this](){
            gf::Log::debug("Max unit : %d\n", max_unit);
            if (max_unit > 2) selected_unit = (selected_unit+1 > max_unit-1) ? min_unit : selected_unit+1;
        });
        s_validate.setCallback([this](){
            gf::Log::debug("Validate the unit selection\n");

            auto& map = game_hub.mainScene.m_map;
            auto& model = game_hub.clientNetwork.getGameModel();
            auto& curr_land = model.get_land_by_name(map.curr_selection->getName());

            switch(model.get_current_phase()){
                case TurnPhase::Fortify:
                    gf::Log::debug("Fortify...\n");
                    if(curr_land.getOwner() != game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) Current selection is not owned by player\n");
                    }
                    else {
                        ClientGameSendFortify fortify;
                        fortify.land_id = model.get_land_id_by_name(map.curr_selection->getName());
                        fortify.nb = selected_unit;
                        //
                        game_hub.clientNetwork.send(fortify);
                    }
                    map.reset_selections();
                    break;
                case TurnPhase::Attack:
                    gf::Log::debug("Attack...\n");
                    if(map.old_selection == nullptr){
                        gf::Log::warning("(CLIENT GAME) Waiting for a second land to be chosen\n");
                        break;
                    }
                    if(model.get_land_by_name(map.old_selection->getName()).getOwner() != game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) First selection is not owned by player\n");
                    }
                    else if (model.get_land_by_name(map.old_selection->getName()).getNb_units() <= 1){
                        gf::Log::warning("(CLIENT GAME) First selection does not have enough units to attack !\n");
                    }
                    else if(curr_land.getOwner() == game_hub.clientNetwork.getClientId()){
                        gf::Log::warning("(CLIENT GAME) Second selection is owned by player\n");
                    }
                    else{
                        ClientGameSendAttack attack;
                        attack.attacking_land_id = model.get_land_id_by_name(map.old_selection->getName());
                        attack.defending_land_id = model.get_land_id_by_name(map.curr_selection->getName());
                        attack.attacking_nb_dice = selected_unit;                        
                        //
                        game_hub.clientNetwork.send(attack);
                    }
                    map.reset_selections();
                    break;
                case TurnPhase::Reinforce:
                    gf::Log::debug("Reinforce...\n");
                    //
                    ClientGameSendReinforce reinforce;
                    reinforce.target = model.get_land_id_by_name(map.curr_selection->getName());
                    reinforce.from = model.get_land_id_by_name(map.old_selection->getName());
                    reinforce.nb_troops = selected_unit;
                    //
                    game_hub.clientNetwork.send(reinforce);
                    //
                    map.reset_selections();
                    break;
                case TurnPhase::End:
                    gf::Log::debug("End...\n");
                    map.reset_selections();
                    break;
            }

            hide();
        });
        s_cancel.setCallback([this](){
            gf::Log::debug("Cancel the unit selection\n");
            game_hub.mainScene.m_map.reset_selections();
            hide();
        });
    }

    void UnitSelector::rmCallbacks(){
        s_left.setCallback([](){});
        s_right.setCallback([](){});
        s_validate.setCallback([](){});
        s_cancel.setCallback([](){});
    }

    void UnitSelector::hide() {
        hidden = true;
        selected_unit = min_unit;
        //game_hub.mainScene.m_map.reset_selections();
        rmCallbacks();
    }

    void UnitSelector::show() {
        hidden = false;
        setCallbacks();
    }

    void UnitSelector::setMaxUnit(int max) {
        max_unit = max;
        //selected_unit = min_unit;
    }
    
    void UnitSelector::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        if (hidden) return;
        gf::RoundedRectangleShape background({static_cast<float>(dimensions.x), static_cast<float>(dimensions.y)});
        background.setRadius(10);
        background.setPosition(position);
        background.setColor(HUDColor().buttonColor);
        target.draw(background, states);

        gf::Text text(std::to_string(selected_unit),ressources.getFont(font),20);
        text.setPosition(position + gf::Vector2i({dimensions.x/2, dimensions.y/2}));
        text.setAnchor(gf::Anchor::Center);
        
        target.draw(text, states);



        s_container.render(target, states);
    }
}