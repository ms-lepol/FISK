#include "HudButtons.h"
#include <gf/Log.h>
#include <iostream>



namespace fisk {

     HudButtons::HudButtons(gf::ResourceManager& rm, gf::TextureAtlas& atlas) : 
        ressources(rm), 
        atlas(atlas),
        widg_card(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("buttonCard"),atlas.getTextureRect("buttonCard"),atlas.getTextureRect("buttonCard"))),
        widg_help(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("buttonHelp"),atlas.getTextureRect("buttonHelp"),atlas.getTextureRect("buttonHelp"))),
        widg_settings(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("ButtonSetting"),atlas.getTextureRect("ButtonSetting"),atlas.getTextureRect("ButtonSetting"))),
        widg_quit(gf::SpriteWidget(atlas.getTexture(),atlas.getTextureRect("buttonQuit"),atlas.getTextureRect("buttonQuit"),atlas.getTextureRect("buttonQuit")))
        {
        //Logic
      
        //Rendering


        widg_card.setPosition({0,0});
        widg_help.setPosition({0,64});
        widg_settings.setPosition({0,128});
        widg_quit.setPosition({0,192});


        //Logic
        widg_card.setCallback([this] {
            callbackCardButton();
        });

        widg_container.addWidget(widg_card);
        widg_container.addWidget(widg_help);
        widg_container.addWidget(widg_settings);
        widg_container.addWidget(widg_quit);

        }

    void HudButtons::callbackCardButton() {
        //Logic
        gf::Log::info("CardButton clicked");
    }

    void HudButtons::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        //rendering block by block
        widg_container.render(target,states);
        widg_card.draw(target,states);
    }

}