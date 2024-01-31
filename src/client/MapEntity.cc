#include "MapEntity.h"
#include "LandEntity.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace fisk {
    MapEntity::MapEntity(gf::ResourceManager& rm , unsigned level_id) : 
        ressources(rm)
        {
        ;
        switch (level_id) {
            case 1:
                configureMap1();
                break;
            default:
                break;
        
        }
        

    }



    void  MapEntity::configureMap1(){

        lands["Alaska"] = std::make_unique<LandEntity>("Alaska", 0, pathAlaska, gf::Vector2i(xAlaska,yAlaska),gf::Vector2i(xTextAlaska,yTextAlaska),ressources);
        lands["NorthwestTerritory"] = std::make_unique<LandEntity>("Northwest Territory", 0, pathNorthAmericaTerr, gf::Vector2i(xNorthAmericaTerr,yNorthAmericaTerr),gf::Vector2i(xTextNorthAmericaTerr,yTextNorthAmericaTerr),ressources);
        lands["Greenland"] = std::make_unique<LandEntity>("Greenland", 0, pathGroenland, gf::Vector2i(xGroenland,yGroenland),gf::Vector2i(xTextGroenland,yTextGroenland),ressources);
        lands["Atlanta"] = std::make_unique<LandEntity>("Atlanta", 0, pathAtlanta, gf::Vector2i(xAtlanta,yAtlanta),gf::Vector2i(xTextAtlanta,yTextAtlanta),ressources);
        lands["Ontario"] = std::make_unique<LandEntity>("Ontario", 0, pathOntario, gf::Vector2i(xOntario,yOntario),gf::Vector2i(xTextOntario,yTextOntario),ressources);
        lands["Quebec"] = std::make_unique<LandEntity>("Quebec", 0, pathQuebec, gf::Vector2i(xQuebec,yQuebec),gf::Vector2i(xTextQuebec,yTextQuebec),ressources);
        lands["WesternUnitedStates"] = std::make_unique<LandEntity>("Western United States", 0, pathWestUS, gf::Vector2i(xWestUS,yWestUS),gf::Vector2i(xTextWestUS,yTextWestUS),ressources);
        lands["EasternUnitedStates"] = std::make_unique<LandEntity>("Eastern United States", 0, pathEastUS, gf::Vector2i(xEastUS,yEastUS),gf::Vector2i(xTextEastUS,yTextEastUS),ressources);
        lands["CentralAmerica"] = std::make_unique<LandEntity>("Central America", 0, pathCentralAmerica, gf::Vector2i(xCentralAmerica,yCentralAmerica),gf::Vector2i(xTextCentralAmerica,yTextCentralAmerica),ressources);
        lands["Venezuela"] = std::make_unique<LandEntity>("Venezuela", 0, pathVenezuela, gf::Vector2i(xVenezuela,yVenezuela),gf::Vector2i(xTextVenezuela,yTextVenezuela),ressources);
        lands["Peru"] = std::make_unique<LandEntity>("Peru", 0, pathPeru, gf::Vector2i(xPeru,yPeru),gf::Vector2i(xTextPeru,yTextPeru),ressources);
        lands["Brazil"] = std::make_unique<LandEntity>("Brazil", 0, pathBrazil, gf::Vector2i(xBrazil,yBrazil),gf::Vector2i(xTextBrazil,yTextBrazil),ressources);
        lands["Argentina"] = std::make_unique<LandEntity>("Argentina", 0, pathArgentina, gf::Vector2i(xArgentina,yArgentina),gf::Vector2i(xTextArgentina,yTextArgentina),ressources);
        lands["GreatBritain"] = std::make_unique<LandEntity>("Great Britain", 0, pathGB, gf::Vector2i(xGB,yGB),gf::Vector2i(xTextGB,yTextGB),ressources);
        lands["Scandinavia"] = std::make_unique<LandEntity>("Scandinavia", 0, pathScandinavia, gf::Vector2i(xScandinavia,yScandinavia),gf::Vector2i(xTextScandinavia,yTextScandinavia),ressources);
        lands["NorthernEurope"] = std::make_unique<LandEntity>("Northern Europe", 0, pathEuropeNorth, gf::Vector2i(xEuropeNorth,yEuropeNorth),gf::Vector2i(xTextEuropeNorth,yTextEuropeNorth),ressources);
        lands["SouthernEurope"] = std::make_unique<LandEntity>("Southern Europe", 0, pathEuropeSouth, gf::Vector2i(xEuropeSouth,yEuropeSouth),gf::Vector2i(xTextEuropeSouth,yTextEuropeSouth),ressources);
        lands["WesternEurope"] = std::make_unique<LandEntity>("Western Europe", 0, pathEuropeWest, gf::Vector2i(xEuropeWest,yEuropeWest),gf::Vector2i(xTextEuropeWest,yTextEuropeWest),ressources);
        lands["EasternEurope"] = std::make_unique<LandEntity>("Eastern Europe", 0, pathEuropeEast, gf::Vector2i(xEuropeEast,yEuropeEast),gf::Vector2i(xTextEuropeEast,yTextEuropeEast),ressources);
        lands["NorthAfrica"] = std::make_unique<LandEntity>("North Africa", 0, pathNorthAfrica, gf::Vector2i(xNorthAfrica,yNorthAfrica),gf::Vector2i(xTextNorthAfrica,yTextNorthAfrica),ressources);
        lands["Egypt"] = std::make_unique<LandEntity>("Egypt", 0, pathEgypte, gf::Vector2i(xEgypte,yEgypte),gf::Vector2i(xTextEgypte,yTextEgypte),ressources);
        lands["EastAfrica"] = std::make_unique<LandEntity>("East Africa", 0, pathEastAfrica, gf::Vector2i(xEastAfrica,yEastAfrica),gf::Vector2i(xTextEastAfrica,yTextEastAfrica),ressources);
        lands["Congo"] = std::make_unique<LandEntity>("Congo", 0, pathCongo, gf::Vector2i(xCongo,yCongo),gf::Vector2i(xTextCongo,yTextCongo),ressources);
        lands["SouthAfrica"] = std::make_unique<LandEntity>("South Africa", 0, pathSouthAfrica, gf::Vector2i(xSouthAfrica,ySouthAfrica),gf::Vector2i(xTextSouthAfrica,yTextSouthAfrica),ressources);
        lands["Madagascar"] = std::make_unique<LandEntity>("Madagascar", 0, pathMadagascar, gf::Vector2i(xMadagascar,yMadagascar),gf::Vector2i(xTextMadagascar,yTextMadagascar),ressources);
        lands["Ural"] = std::make_unique<LandEntity>("Ural", 0, pathUral, gf::Vector2i(xUral,yUral),gf::Vector2i(xTextUral,yTextUral),ressources);
        lands["Siberia"] = std::make_unique<LandEntity>("Siberia", 0, pathSiberia, gf::Vector2i(xSiberia,ySiberia),gf::Vector2i(xTextSiberia,yTextSiberia),ressources);
        lands["Mongolia"] = std::make_unique<LandEntity>("Mongolia", 0, pathMongolia, gf::Vector2i(xMongolia,yMongolia),gf::Vector2i(xTextMongolia,yTextMongolia),ressources);
        lands["Japan"] = std::make_unique<LandEntity>("Japan", 0, pathJapan, gf::Vector2i(xJapan,yJapan),gf::Vector2i(xTextJapan,yTextJapan),ressources);
        lands["Afghanistan"] = std::make_unique<LandEntity>("Afghanistan", 0, pathAfhganistan, gf::Vector2i(xAfhganistan,yAfhganistan),gf::Vector2i(xTextAfhganistan,yTextAfhganistan),ressources);
        lands["China"] = std::make_unique<LandEntity>("China", 0, pathChina, gf::Vector2i(xChina,yChina),gf::Vector2i(xTextChina,yTextChina),ressources);
        lands["MiddleEast"] = std::make_unique<LandEntity>("Middle East", 0, pathMiddleEast, gf::Vector2i(xMiddleEast,yMiddleEast),gf::Vector2i(xTextMiddleEast,yTextMiddleEast),ressources);
        lands["India"] = std::make_unique<LandEntity>("India", 0, pathIndia, gf::Vector2i(xIndia,yIndia),gf::Vector2i(xTextIndia,yTextIndia),ressources);
        lands["Indonesia"] = std::make_unique<LandEntity>("Indonesia", 0, pathIndonesia, gf::Vector2i(xIndonesia,yIndonesia),gf::Vector2i(xTextIndonesia,yTextIndonesia),ressources);
        lands["NewZealand"] = std::make_unique<LandEntity>("New Zealand", 0, pathNewZealand, gf::Vector2i(xNewZealand,yNewZealand),gf::Vector2i(xTextNewZealand,yTextNewZealand),ressources);
        lands["WesternAustralia"] = std::make_unique<LandEntity>("Western Australia", 0, pathWestAustralia, gf::Vector2i(xWestAustralia,yWestAustralia),gf::Vector2i(xTextWestAustralia,yTextWestAustralia),ressources);
        lands["EasternAustralia"] = std::make_unique<LandEntity>("Eastern Australia", 0, pathEastAustralia, gf::Vector2i(xEastAustralia,yEastAustralia),gf::Vector2i(xTextEastAustralia,yTextEastAustralia),ressources);
        lands["Thailande"] = std::make_unique<LandEntity>("Thailande", 0, pathThai, gf::Vector2i(xThai,yThai),gf::Vector2i(xTextThai,yTextThai),ressources);
        
        for (auto& [key,value] : lands) {
            widg_container.addWidget(value->spr_widg);
        }

        
    }

    void MapEntity::changeLandColor(std::string land_name, gf::Color4f color) {
        if (lands.find(land_name) != lands.end()) lands[land_name]->setColor(color);
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