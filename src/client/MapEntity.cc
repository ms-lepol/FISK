#include "MapEntity.h"
#include "LandEntity.h"
#include <cstdlib>
#include <iostream>
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

    MapEntity::~MapEntity() {
        for (auto& [key,value] : lands) {
            delete value;
        }
    }


    void  MapEntity::configureMap1(){

        LandEntity* Alaska = new LandEntity("Alaska", 0, pathAlaska, gf::Vector2i(xAlaska,yAlaska),gf::Vector2i(xTextAlaska,yTextAlaska),ressources);
        LandEntity* NorthwestTerritory = new LandEntity("Northwest Territory", 0, pathNorthAmericaTerr, gf::Vector2i(xNorthAmericaTerr,yNorthAmericaTerr),gf::Vector2i(xTextNorthAmericaTerr,yTextNorthAmericaTerr),ressources);
        LandEntity* Greenland = new LandEntity("Greenland", 0, pathGroenland, gf::Vector2i(xGroenland,yGroenland),gf::Vector2i(xTextGroenland,yTextGroenland),ressources);
        LandEntity* Atlanta = new LandEntity("Atlanta", 0, pathAtlanta, gf::Vector2i(xAtlanta,yAtlanta),gf::Vector2i(xTextAtlanta,yTextAtlanta),ressources);
        LandEntity* Ontario = new LandEntity("Ontario", 0, pathOntario, gf::Vector2i(xOntario,yOntario),gf::Vector2i(xTextOntario,yTextOntario),ressources);
        LandEntity* Quebec = new LandEntity("Quebec", 0, pathQuebec, gf::Vector2i(xQuebec,yQuebec),gf::Vector2i(xTextQuebec,yTextQuebec),ressources);
        LandEntity* WesternUnitedStates = new LandEntity("Western United States", 0, pathWestUS, gf::Vector2i(xWestUS,yWestUS),gf::Vector2i(xTextWestUS,yTextWestUS),ressources);
        LandEntity* EasternUnitedStates = new LandEntity("Eastern United States", 0, pathEastUS, gf::Vector2i(xEastUS,yEastUS),gf::Vector2i(xTextEastUS,yTextEastUS),ressources);
        LandEntity* CentralAmerica = new LandEntity("Central America", 0, pathCentralAmerica, gf::Vector2i(xCentralAmerica,yCentralAmerica),gf::Vector2i(xTextCentralAmerica,yTextCentralAmerica),ressources);
        LandEntity* Venezuela = new LandEntity("Venezuela", 0, pathVenezuela, gf::Vector2i(xVenezuela,yVenezuela),gf::Vector2i(xTextVenezuela,yTextVenezuela),ressources);
        LandEntity* Peru = new LandEntity("Peru", 0, pathPeru, gf::Vector2i(xPeru,yPeru),gf::Vector2i(xTextPeru,yTextPeru),ressources);
        LandEntity* Brazil = new LandEntity("Brazil", 0, pathBrazil, gf::Vector2i(xBrazil,yBrazil),gf::Vector2i(xTextBrazil,yTextBrazil),ressources);
        LandEntity* Argentina = new LandEntity("Argentina", 0, pathArgentina, gf::Vector2i(xArgentina,yArgentina),gf::Vector2i(xTextArgentina,yTextArgentina),ressources);
        LandEntity* GreatBritain = new LandEntity("Great Britain", 0, pathGB, gf::Vector2i(xGB,yGB),gf::Vector2i(xTextGB,yTextGB),ressources);
        LandEntity* Scandinavia = new LandEntity("Scandinavia", 0, pathScandinavia, gf::Vector2i(xScandinavia,yScandinavia),gf::Vector2i(xTextScandinavia,yTextScandinavia),ressources);
        LandEntity* NorthernEurope = new LandEntity("Northern Europe", 0, pathEuropeNorth, gf::Vector2i(xEuropeNorth,yEuropeNorth),gf::Vector2i(xTextEuropeNorth,yTextEuropeNorth),ressources);
        LandEntity* SouthernEurope = new LandEntity("Southern Europe", 0, pathEuropeSouth, gf::Vector2i(xEuropeSouth,yEuropeSouth),gf::Vector2i(xTextEuropeSouth,yTextEuropeSouth),ressources);
        LandEntity* WesternEurope = new LandEntity("Western Europe", 0, pathEuropeWest, gf::Vector2i(xEuropeWest,yEuropeWest),gf::Vector2i(xTextEuropeWest,yTextEuropeWest),ressources);
        LandEntity* EasternEurope = new LandEntity("Eastern Europe", 0, pathEuropeEast, gf::Vector2i(xEuropeEast,yEuropeEast),gf::Vector2i(xTextEuropeEast,yTextEuropeEast),ressources);
        LandEntity* NorthAfrica = new LandEntity("North Africa", 0, pathNorthAfrica, gf::Vector2i(xNorthAfrica,yNorthAfrica),gf::Vector2i(xTextNorthAfrica,yTextNorthAfrica),ressources);
        LandEntity* Egypt = new LandEntity("Egypt", 0, pathEgypte, gf::Vector2i(xEgypte,yEgypte),gf::Vector2i(xTextEgypte,yTextEgypte),ressources);
        LandEntity* EastAfrica = new LandEntity("East Africa", 0, pathEastAfrica, gf::Vector2i(xEastAfrica,yEastAfrica),gf::Vector2i(xTextEastAfrica,yTextEastAfrica),ressources);
        LandEntity* Congo = new LandEntity("Congo", 0, pathCongo, gf::Vector2i(xCongo,yCongo),gf::Vector2i(xTextCongo,yTextCongo),ressources);
        LandEntity* SouthAfrica = new LandEntity("South Africa", 0, pathSouthAfrica, gf::Vector2i(xSouthAfrica,ySouthAfrica),gf::Vector2i(xTextSouthAfrica,yTextSouthAfrica),ressources);
        LandEntity* Madagascar = new LandEntity("Madagascar", 0, pathMadagascar, gf::Vector2i(xMadagascar,yMadagascar),gf::Vector2i(xTextMadagascar,yTextMadagascar),ressources);
        LandEntity* Ural = new LandEntity("Ural", 0, pathUral, gf::Vector2i(xUral,yUral),gf::Vector2i(xTextUral,yTextUral),ressources);
        LandEntity* Siberia = new LandEntity("Siberia", 0, pathSiberia, gf::Vector2i(xSiberia,ySiberia),gf::Vector2i(xTextSiberia,yTextSiberia),ressources);
        LandEntity* Mongolia = new LandEntity("Mongolia", 0, pathMongolia, gf::Vector2i(xMongolia,yMongolia),gf::Vector2i(xTextMongolia,yTextMongolia),ressources);
        LandEntity* Japan = new LandEntity("Japan", 0, pathJapan, gf::Vector2i(xJapan,yJapan),gf::Vector2i(xTextJapan,yTextJapan),ressources);
        LandEntity* Afghanistan = new LandEntity("Afghanistan", 0, pathAfhganistan, gf::Vector2i(xAfhganistan,yAfhganistan),gf::Vector2i(xTextAfhganistan,yTextAfhganistan),ressources);
        LandEntity* China = new LandEntity("China", 0, pathChina, gf::Vector2i(xChina,yChina),gf::Vector2i(xTextChina,yTextChina),ressources);
        LandEntity* MiddleEast = new LandEntity("Middle East", 0, pathMiddleEast, gf::Vector2i(xMiddleEast,yMiddleEast),gf::Vector2i(xTextMiddleEast,yTextMiddleEast),ressources);
        LandEntity* India = new LandEntity("India", 0, pathIndia, gf::Vector2i(xIndia,yIndia),gf::Vector2i(xTextIndia,yTextIndia),ressources);
        LandEntity* Indonesia = new LandEntity("Indonesia", 0, pathIndonesia, gf::Vector2i(xIndonesia,yIndonesia),gf::Vector2i(xTextIndonesia,yTextIndonesia),ressources);
        LandEntity* NewZealand = new LandEntity("New Zealand", 0, pathNewZealand, gf::Vector2i(xNewZealand,yNewZealand),gf::Vector2i(xTextNewZealand,yTextNewZealand),ressources);
        LandEntity* WesternAustralia = new LandEntity("Western Australia", 0, pathWestAustralia, gf::Vector2i(xWestAustralia,yWestAustralia),gf::Vector2i(xTextWestAustralia,yTextWestAustralia),ressources);
        LandEntity* EasternAustralia = new LandEntity("Eastern Australia", 0, pathEastAustralia, gf::Vector2i(xEastAustralia,yEastAustralia),gf::Vector2i(xTextEastAustralia,yTextEastAustralia),ressources);
        LandEntity* Thailande = new LandEntity("Thailande", 0, pathThai, gf::Vector2i(xThai,yThai),gf::Vector2i(xTextThai,yTextThai),ressources);

        lands["Alaska"]=Alaska;
        lands["NorthwestTerritory"]=NorthwestTerritory;
        lands["Greenland"]=Greenland;
        lands["Atlanta"]=Atlanta;
        lands["Ontario"]=Ontario;
        lands["Quebec"]=Quebec;
        lands["WesternUnitedStates"]=WesternUnitedStates;
        lands["EasternUnitedStates"]=EasternUnitedStates;
        lands["CentralAmerica"]=CentralAmerica;
        lands["Venezuela"]=Venezuela;
        lands["Peru"]=Peru;
        lands["Brazil"]=Brazil;
        lands["Argentina"]=Argentina;
        lands["GreatBritain"]=GreatBritain;
        lands["Scandinavia"]=Scandinavia;
        lands["NorthernEurope"]=NorthernEurope;
        lands["SouthernEurope"]=SouthernEurope;
        lands["WesternEurope"]=WesternEurope;
        lands["EasternEurope"]=EasternEurope;
        lands["NorthAfrica"]=NorthAfrica;
        lands["Egypt"]=Egypt;
        lands["EastAfrica"]=EastAfrica;
        lands["Congo"]=Congo;
        lands["SouthAfrica"]=SouthAfrica;
        lands["Madagascar"]=Madagascar;
        lands["Ural"]=Ural;
        lands["Siberia"]=Siberia;
        lands["Mongolia"]=Mongolia;
        lands["Japan"]=Japan;
        lands["Afghanistan"]=Afghanistan;
        lands["China"]=China;
        lands["MiddleEast"]=MiddleEast;
        lands["India"]=India;
        lands["Indonesia"]=Indonesia;
        lands["NewZealand"]=NewZealand;
        lands["WesternAustralia"]=WesternAustralia;
        lands["EasternAustralia"]=EasternAustralia;
        lands["Thailande"]=Thailande;

        
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