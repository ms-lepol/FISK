#include "MapEntity.h"
#include "LandEntity.h"
#include <cstdlib>
#include <iostream>

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

        LandEntity* Alaska = new LandEntity("Alaska", 0, pathAlaska, gf::Vector2i(xAlaska,yAlaska),ressources);
        LandEntity* NorthwestTerritory = new LandEntity("Northwest Territory", 0, pathNorthAmericaTerr, gf::Vector2i(xNorthAmericaTerr,yNorthAmericaTerr),ressources);
        LandEntity* Greenland = new LandEntity("Greenland", 0, pathGroenland, gf::Vector2i(xGroenland,yGroenland),ressources);
        LandEntity* Alberta = new LandEntity("Alberta", 0, pathAtlanta, gf::Vector2i(xAtlanta,yAtlanta),ressources);
        LandEntity* Ontario = new LandEntity("Ontario", 0, pathOntario, gf::Vector2i(xOntario,yOntario),ressources);
        LandEntity* Quebec = new LandEntity("Quebec", 0, pathQuebec, gf::Vector2i(xQuebec,yQuebec),ressources);
        LandEntity* WesternUnitedStates = new LandEntity("Western United States", 0, pathWestUS, gf::Vector2i(xWestUS,yWestUS),ressources);
        LandEntity* EasternUnitedStates = new LandEntity("Eastern United States", 0, pathEastUS, gf::Vector2i(xEastUS,yEastUS),ressources);
        LandEntity* CentralAmerica = new LandEntity("Central America", 0, pathCentralAmerica, gf::Vector2i(xCentralAmerica,yCentralAmerica),ressources);
        LandEntity* Venezuela = new LandEntity("Venezuela", 0, pathVenezuela, gf::Vector2i(xVenezuela,yVenezuela),ressources);
        LandEntity* Peru = new LandEntity("Peru", 0, pathPeru, gf::Vector2i(xPeru,yPeru),ressources);
        LandEntity* Brazil = new LandEntity("Brazil", 0, pathBrazil, gf::Vector2i(xBrazil,yBrazil),ressources);
        LandEntity* Argentina = new LandEntity("Argentina", 0, pathArgentina, gf::Vector2i(xArgentina,yArgentina),ressources);
        LandEntity* GreatBritain = new LandEntity("Great Britain", 0, pathGB, gf::Vector2i(xGB,yGB),ressources);
        LandEntity* Scandinavia = new LandEntity("Scandinavia", 0, pathScandinavia, gf::Vector2i(xScandinavia,yScandinavia),ressources);
        LandEntity* NorthernEurope = new LandEntity("Northern Europe", 0, pathEuropeNorth, gf::Vector2i(xEuropeNorth,yEuropeNorth),ressources);
        LandEntity* SouthernEurope = new LandEntity("Southern Europe", 0, pathEuropeSouth, gf::Vector2i(xEuropeSouth,yEuropeSouth),ressources);
        LandEntity* WesternEurope = new LandEntity("Western Europe", 0, pathEuropeWest, gf::Vector2i(xEuropeWest,yEuropeWest),ressources);
        LandEntity* EasternEurope = new LandEntity("Eastern Europe", 0, pathEuropeEast, gf::Vector2i(xEuropeEast,yEuropeEast),ressources);
        LandEntity* NorthAfrica = new LandEntity("North Africa", 0, pathNorthAfrica, gf::Vector2i(xNorthAfrica,yNorthAfrica),ressources);
        LandEntity* Egypt = new LandEntity("Egypt", 0, pathEgypte, gf::Vector2i(xEgypte,yEgypte),ressources);
        LandEntity* EastAfrica = new LandEntity("East Africa", 0, pathEastAfrica, gf::Vector2i(xEastAfrica,yEastAfrica),ressources);
        LandEntity* Congo = new LandEntity("Congo", 0, pathCongo, gf::Vector2i(xCongo,yCongo),ressources);
        LandEntity* SouthAfrica = new LandEntity("South Africa", 0, pathSouthAfrica, gf::Vector2i(xSouthAfrica,ySouthAfrica),ressources);
        LandEntity* Madagascar = new LandEntity("Madagascar", 0, pathMadagascar, gf::Vector2i(xMadagascar,yMadagascar),ressources);
        LandEntity* Ural = new LandEntity("Ural", 0, pathUral, gf::Vector2i(xUral,yUral),ressources);
        LandEntity* Siberia = new LandEntity("Siberia", 0, pathSiberia, gf::Vector2i(xSiberia,ySiberia),ressources);
        LandEntity* Mongolia = new LandEntity("Mongolia", 0, pathMongolia, gf::Vector2i(xMongolia,yMongolia),ressources);
        LandEntity* Japan = new LandEntity("Japan", 0, pathJapan, gf::Vector2i(xJapan,yJapan),ressources);
        LandEntity* Afghanistan = new LandEntity("Afghanistan", 0, pathAfhganistan, gf::Vector2i(xAfhganistan,yAfhganistan),ressources);
        LandEntity* China = new LandEntity("China", 0, pathChina, gf::Vector2i(xChina,yChina),ressources);
        LandEntity* MiddleEast = new LandEntity("Middle East", 0, pathMiddleEast, gf::Vector2i(xMiddleEast,yMiddleEast),ressources);
        LandEntity* India = new LandEntity("India", 0, pathIndia, gf::Vector2i(xIndia,yIndia),ressources);
        LandEntity* Indonesia = new LandEntity("Indonesia", 0, pathIndonesia, gf::Vector2i(xIndonesia,yIndonesia),ressources);
        LandEntity* NewZealand = new LandEntity("New Zealand", 0, pathNewZealand, gf::Vector2i(xNewZealand,yNewZealand),ressources);
        LandEntity* WesternAustralia = new LandEntity("Western Australia", 0, pathWestAustralia, gf::Vector2i(xWestAustralia,yWestAustralia),ressources);
        LandEntity* EasternAustralia = new LandEntity("Eastern Australia", 0, pathEastAustralia, gf::Vector2i(xEastAustralia,yEastAustralia),ressources);
      
        lands["Alaska"]=Alaska;
        lands["NorthwestTerritory"]=NorthwestTerritory;
        lands["Greenland"]=Greenland;
        lands["Alberta"]=Alberta;
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
        
        for (auto& [key,value] : lands) {
            widg_container.addWidget(value->spr_widg);
        }
    }
    
    void MapEntity::render(gf::RenderTarget& target, const gf::RenderStates& states) {
        for (auto& [key,value] : lands) {
            value->render(target);
        }
    }
}