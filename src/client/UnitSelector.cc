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
        selected_unit = 0;
        max_unit = 0;
       
        
        s_container.addWidget(s_left);
        s_container.addWidget(s_right);
        s_container.addWidget(s_validate);
        s_container.addWidget(s_cancel);

        s_left.setCallback([this](){
            selected_unit = (selected_unit-1+max_unit)%max_unit;
            
        });
        s_right.setCallback([this](){
            selected_unit = (selected_unit+1)%max_unit;
        });
        s_validate.setCallback([this](){
            gf::Log::debug("Validate the unit selection\n");
            kill();
        });
        s_cancel.setCallback([this](){
            gf::Log::debug("Cancel the unit selection\n");
            kill();
        });

        s_left.setPosition(position + gf::Vector2i({dimensions.x/4, dimensions.y/2}));
        s_right.setPosition(position + gf::Vector2i({3*dimensions.x/4, dimensions.y/2}));
        s_validate.setPosition(position + gf::Vector2i({dimensions.x/4, 3*dimensions.y/4}));
        s_cancel.setPosition(position + gf::Vector2i({3*dimensions.x/4, 3*dimensions.y/4}));

        s_left.setPadding(5);
        s_right.setPadding(5);
        s_validate.setPadding(5);
        s_cancel.setPadding(5);

        s_left.setDefaultTextColor(HUDColor().backgroundColor);
        s_right.setDefaultTextColor(HUDColor().backgroundColor);
        s_validate.setDefaultTextColor(HUDColor().backgroundColor);
        s_cancel.setDefaultTextColor(HUDColor().backgroundColor);

        s_left.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_right.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_validate.setDefaultBackgroundColor(HUDColor().buttonColor);
        s_cancel.setDefaultBackgroundColor(HUDColor().buttonColor);

        s_validate.setAnchor(gf::Anchor::Center);
        s_cancel.setAnchor(gf::Anchor::Center);

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

    }

    void UnitSelector::setMaxUnit(Land& land_clicked) {
        max_unit = land_clicked.getNb_units();
        selected_unit = 0;
    }
    
    void UnitSelector::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        gf::RoundedRectangleShape background({static_cast<float>(dimensions.x), static_cast<float>(dimensions.y)});
        background.setRadius(10);
        background.setPosition(position);
        background.setColor(HUDColor().buttonColor);
        target.draw(background, states);

        gf::Text text(std::to_string(selected_unit),ressources.getFont(font),20);
        text.setPosition(position + gf::Vector2i({dimensions.x/2, dimensions.y/2}));
        text.setAnchor(gf::Anchor::Center);
        text.setAlignment(gf::Alignment::Center);
        target.draw(text, states);



        s_container.render(target, states);
    }
}