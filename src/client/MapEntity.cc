#include "MapEntity.h" 
#include "CardScene.h"
#include "LandEntity.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace fisk {
    MapEntity::MapEntity(GameHub& gm , unsigned level_id) : 
    game_hub(gm),
    old_selection(nullptr),
    curr_selection(nullptr)
    {
        switch (level_id) {
            case 1:
                configureMap1();
                break;
            default:
                break;
        }
    }

    void MapEntity::select(LandEntity* e){
        old_selection = curr_selection;
        curr_selection = e;
    }

    void MapEntity::reset_selections(){
        old_selection = nullptr;
        curr_selection = nullptr;
    }
    
    void  MapEntity::configureMap1(){

        lands["Alaska"] = std::make_unique<LandEntity>("Alaska", pathAlaska, gf::Vector2i(xAlaska,yAlaska),gf::Vector2i(xTextAlaska,yTextAlaska),game_hub);
        lands["NorthwestTerritory"] = std::make_unique<LandEntity>("Northwest Territory", pathNorthAmericaTerr, gf::Vector2i(xNorthAmericaTerr,yNorthAmericaTerr),gf::Vector2i(xTextNorthAmericaTerr,yTextNorthAmericaTerr),game_hub);
        lands["Greenland"] = std::make_unique<LandEntity>("Greenland", pathGroenland, gf::Vector2i(xGroenland,yGroenland),gf::Vector2i(xTextGroenland,yTextGroenland),game_hub);
        lands["Atlanta"] = std::make_unique<LandEntity>("Atlanta", pathAtlanta, gf::Vector2i(xAtlanta,yAtlanta),gf::Vector2i(xTextAtlanta,yTextAtlanta),game_hub);
        lands["Ontario"] = std::make_unique<LandEntity>("Ontario", pathOntario, gf::Vector2i(xOntario,yOntario),gf::Vector2i(xTextOntario,yTextOntario),game_hub);
        lands["Quebec"] = std::make_unique<LandEntity>("Quebec", pathQuebec, gf::Vector2i(xQuebec,yQuebec),gf::Vector2i(xTextQuebec,yTextQuebec),game_hub);
        lands["WesternUnitedStates"] = std::make_unique<LandEntity>("Western United States", pathWestUS, gf::Vector2i(xWestUS,yWestUS),gf::Vector2i(xTextWestUS,yTextWestUS),game_hub);
        lands["EasternUnitedStates"] = std::make_unique<LandEntity>("Eastern United States", pathEastUS, gf::Vector2i(xEastUS,yEastUS),gf::Vector2i(xTextEastUS,yTextEastUS),game_hub);
        lands["CentralAmerica"] = std::make_unique<LandEntity>("Central America", pathCentralAmerica, gf::Vector2i(xCentralAmerica,yCentralAmerica),gf::Vector2i(xTextCentralAmerica,yTextCentralAmerica),game_hub);
        lands["Venezuela"] = std::make_unique<LandEntity>("Venezuela", pathVenezuela, gf::Vector2i(xVenezuela,yVenezuela),gf::Vector2i(xTextVenezuela,yTextVenezuela),game_hub);
        lands["Peru"] = std::make_unique<LandEntity>("Peru", pathPeru, gf::Vector2i(xPeru,yPeru),gf::Vector2i(xTextPeru,yTextPeru),game_hub);
        lands["Brazil"] = std::make_unique<LandEntity>("Brazil", pathBrazil, gf::Vector2i(xBrazil,yBrazil),gf::Vector2i(xTextBrazil,yTextBrazil),game_hub);
        lands["Argentina"] = std::make_unique<LandEntity>("Argentina", pathArgentina, gf::Vector2i(xArgentina,yArgentina),gf::Vector2i(xTextArgentina,yTextArgentina),game_hub);
        lands["GreatBritain"] = std::make_unique<LandEntity>("Great Britain", pathGB, gf::Vector2i(xGB,yGB),gf::Vector2i(xTextGB,yTextGB),game_hub);
        lands["Scandinavia"] = std::make_unique<LandEntity>("Scandinavia", pathScandinavia, gf::Vector2i(xScandinavia,yScandinavia),gf::Vector2i(xTextScandinavia,yTextScandinavia),game_hub);
        lands["NorthernEurope"] = std::make_unique<LandEntity>("Northern Europe", pathEuropeNorth, gf::Vector2i(xEuropeNorth,yEuropeNorth),gf::Vector2i(xTextEuropeNorth,yTextEuropeNorth),game_hub);
        lands["SouthernEurope"] = std::make_unique<LandEntity>("Southern Europe", pathEuropeSouth, gf::Vector2i(xEuropeSouth,yEuropeSouth),gf::Vector2i(xTextEuropeSouth,yTextEuropeSouth),game_hub);
        lands["WesternEurope"] = std::make_unique<LandEntity>("Western Europe", pathEuropeWest, gf::Vector2i(xEuropeWest,yEuropeWest),gf::Vector2i(xTextEuropeWest,yTextEuropeWest),game_hub);
        lands["EasternEurope"] = std::make_unique<LandEntity>("Eastern Europe", pathEuropeEast, gf::Vector2i(xEuropeEast,yEuropeEast),gf::Vector2i(xTextEuropeEast,yTextEuropeEast),game_hub);
        lands["NorthAfrica"] = std::make_unique<LandEntity>("North Africa", pathNorthAfrica, gf::Vector2i(xNorthAfrica,yNorthAfrica),gf::Vector2i(xTextNorthAfrica,yTextNorthAfrica),game_hub);
        lands["Egypt"] = std::make_unique<LandEntity>("Egypt", pathEgypte, gf::Vector2i(xEgypte,yEgypte),gf::Vector2i(xTextEgypte,yTextEgypte),game_hub);
        lands["EastAfrica"] = std::make_unique<LandEntity>("East Africa", pathEastAfrica, gf::Vector2i(xEastAfrica,yEastAfrica),gf::Vector2i(xTextEastAfrica,yTextEastAfrica),game_hub);
        lands["Congo"] = std::make_unique<LandEntity>("Congo", pathCongo, gf::Vector2i(xCongo,yCongo),gf::Vector2i(xTextCongo,yTextCongo),game_hub);
        lands["SouthAfrica"] = std::make_unique<LandEntity>("South Africa", pathSouthAfrica, gf::Vector2i(xSouthAfrica,ySouthAfrica),gf::Vector2i(xTextSouthAfrica,yTextSouthAfrica),game_hub);
        lands["Madagascar"] = std::make_unique<LandEntity>("Madagascar", pathMadagascar, gf::Vector2i(xMadagascar,yMadagascar),gf::Vector2i(xTextMadagascar,yTextMadagascar),game_hub);
        lands["Ural"] = std::make_unique<LandEntity>("Ural", pathUral, gf::Vector2i(xUral,yUral),gf::Vector2i(xTextUral,yTextUral),game_hub);
        lands["Siberia"] = std::make_unique<LandEntity>("Siberia", pathSiberia, gf::Vector2i(xSiberia,ySiberia),gf::Vector2i(xTextSiberia,yTextSiberia),game_hub);
        lands["Mongolia"] = std::make_unique<LandEntity>("Mongolia", pathMongolia, gf::Vector2i(xMongolia,yMongolia),gf::Vector2i(xTextMongolia,yTextMongolia),game_hub);
        lands["Japan"] = std::make_unique<LandEntity>("Japan", pathJapan, gf::Vector2i(xJapan,yJapan),gf::Vector2i(xTextJapan,yTextJapan),game_hub);
        lands["Afghanistan"] = std::make_unique<LandEntity>("Afghanistan", pathAfhganistan, gf::Vector2i(xAfhganistan,yAfhganistan),gf::Vector2i(xTextAfhganistan,yTextAfhganistan),game_hub);
        lands["China"] = std::make_unique<LandEntity>("China", pathChina, gf::Vector2i(xChina,yChina),gf::Vector2i(xTextChina,yTextChina),game_hub);
        lands["MiddleEast"] = std::make_unique<LandEntity>("Middle East", pathMiddleEast, gf::Vector2i(xMiddleEast,yMiddleEast),gf::Vector2i(xTextMiddleEast,yTextMiddleEast),game_hub);
        lands["India"] = std::make_unique<LandEntity>("India", pathIndia, gf::Vector2i(xIndia,yIndia),gf::Vector2i(xTextIndia,yTextIndia),game_hub);
        lands["Indonesia"] = std::make_unique<LandEntity>("Indonesia", pathIndonesia, gf::Vector2i(xIndonesia,yIndonesia),gf::Vector2i(xTextIndonesia,yTextIndonesia),game_hub);
        lands["NewZealand"] = std::make_unique<LandEntity>("New Zealand", pathNewZealand, gf::Vector2i(xNewZealand,yNewZealand),gf::Vector2i(xTextNewZealand,yTextNewZealand),game_hub);
        lands["WesternAustralia"] = std::make_unique<LandEntity>("Western Australia", pathWestAustralia, gf::Vector2i(xWestAustralia,yWestAustralia),gf::Vector2i(xTextWestAustralia,yTextWestAustralia),game_hub);
        lands["EasternAustralia"] = std::make_unique<LandEntity>("Eastern Australia", pathEastAustralia, gf::Vector2i(xEastAustralia,yEastAustralia),gf::Vector2i(xTextEastAustralia,yTextEastAustralia),game_hub);
        lands["Thailande"] = std::make_unique<LandEntity>("Thailande", pathThai, gf::Vector2i(xThai,yThai),gf::Vector2i(xTextThai,yTextThai),game_hub);
        
        for (auto& [key,value] : lands) {
            widg_container.addWidget(value->spr_widg);
        }

        
    }

    void MapEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        std::vector<std::string> keysSelected;
        for (auto& [key,value] : lands) {
            if (value->isSelected()){
                keysSelected.push_back(key);
            } else {
                value->render(target,states);
            }
        }
        
        for (auto key : keysSelected){
            lands[key]->renderSelected(target,states);
        }
    }
}
