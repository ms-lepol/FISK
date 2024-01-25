#include "LobbyPlayer.h"
#include "FiskColors.h"
#include <gf/Font.h>
#include <gf/Log.h>
#include <gf/ResourceManager.h>
#include <gf/Text.h>

#define width 400
#define height 100

namespace fisk {

    constexpr gf::Vector2f ViewSize = {1280.0f, 720.0f};
    int LobbyPlayer::nextPlot = 0;

    LobbyPlayer::LobbyPlayer(gf::ResourceManager& rm): rm(rm)
    ,font(rm.getFont("font/PixelSplitter-Bold.ttf"))
    ,l_hudAtlas(gf::TextureAtlas("../data/sprites/ui_atlas.xml",rm)){
        const int marginX = 50;
        const int marginY = 20;

        int line1x = ViewSize.x / 2 - width - marginX;
        int line1y = ViewSize.y / 2 - height - marginY;
        int line2x = ViewSize.x / 2 + marginX;
        int line2y = ViewSize.y / 2 + marginY;
    

        l_hudAtlas.setTexture(rm.getTexture("sprites/fisk_ui.png"));

        nextPlot++;
        switch (LobbyPlayer::nextPlot) {
            case 1:
                position = {line1x,line1y};
                break;
            case 2:
                position = { line1x, line2y };
                break;
            case 3:
                position = { line2x, line1y };
                break;
            case 4:
                position = { line2x, line2y };
                break;
            default:
                break;
        }

        positionName = { position.x + width/2, position.y + height/2};
        positionSprite = { position.x + width, position.y + height/2 - 32 };
        color = HUDColor().plotUnfilled;
        sprite = gf::Sprite();
        sprite.setPosition(positionSprite);
        name = "Waiting for player...";
        plotIsFilled = false;
        isReady = false;
    }

    void LobbyPlayer::render(gf::RenderTarget& target, const gf::RenderStates& states){
            if (plotIsFilled){
                color = HUDColor().buttonColor;
            }


            gf::RoundedRectangleShape rect;
            rect.setSize({ width, height });
            rect.setRadius(10);
            rect.setColor(color);
            rect.setPosition(position);
            target.draw(rect, states);

            gf::Text text;
            text.setString(name);
            text.setFont(font);
            text.setColor(HUDColor().backgroundColor);
            text.setCharacterSize(20);
            text.setPosition(positionName);
            text.setAnchor(gf::Anchor::Center);
             
           
            target.draw(text, states);

            if(!plotIsFilled){
               if (isReady){
                   sprite.setTexture(l_hudAtlas.getTexture(), l_hudAtlas.getTextureRect("greenCheck"));
                } else {
                   sprite.setTexture(l_hudAtlas.getTexture(), l_hudAtlas.getTextureRect("redCross"));
                }
                sprite.setPosition(positionSprite);
                target.draw(sprite, states);
            }


    }

    void LobbyPlayer::update(gf::Time time){
        
    }
    
    
}