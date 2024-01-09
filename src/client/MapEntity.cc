#include "MapEntity.h"

namespace fisk {
    MapEntity::MapEntity(gf::ResourceManager& rm , unsigned level_id) : 
        //map(gf::Vector2i(10,10)),
        ressources(rm)
        ,map("Alaska", 0, pathAlaska, gf::Vector2i(xAlaska,yAlaska),rm)
        {
        
        switch (level_id) {
            case 1:
                //configureMap1();
                break;
            default:
                break;
        
        }
        configureMap1();
    }

    void MapEntity::configureMap1(){
        // North America
         //Continent NorthAmericaContinent("North America", 5);

        LandEntity Alaska = LandEntity("Alaska", 0, pathAlaska, gf::Vector2i(xAlaska,yAlaska),ressources);
        
        
      
        /* NorthAmericaContinent.addLand(LandSprite("Northwest Territory", 0, gf::Color::Red, pathNorthAmericaTerr, gf::Vector2i(xNorthAmericaTerr,yNorthAmericaTerr)));
        NorthAmericaContinent.addLand(LandSprite("Greenland", 0, gf::Color::Red, pathGroenland, gf::Vector2i(xGroenland,yGroenland)));
        NorthAmericaContinent.addLand(LandSprite("Alberta", 0, gf::Color::Red, pathAtlanta, gf::Vector2i(xAtlanta,yAtlanta)));
        NorthAmericaContinent.addLand(LandSprite("Ontario", 0, gf::Color::Red, pathOntario, gf::Vector2i(xOntario,yOntario)));
        NorthAmericaContinent.addLand(LandSprite("Quebec", 0, gf::Color::Red, pathQuebec, gf::Vector2i(xQuebec,yQuebec)));
        NorthAmericaContinent.addLand(LandSprite("Western United States", 0, gf::Color::Red, pathWestUS, gf::Vector2i(xWestUS,yWestUS)));
        NorthAmericaContinent.addLand(LandSprite("Eastern United States", 0, gf::Color::Red, pathEastUS, gf::Vector2i(xEastUS,yEastUS)));
        NorthAmericaContinent.addLand(LandSprite("Central America", 0, gf::Color::Red, pathCentralAmerica, gf::Vector2i(xCentralAmerica,yCentralAmerica)));
        */
        //this->addContinent(&NorthAmericaContinent);

        // South America
       /*  
        Continent SouthAmericaContinent("South America", 2);
        SouthAmericaContinent.addLand(LandSprite("Venezuela", 0, gf::Color::Red, pathVenezuela, gf::Vector2i(xVenezuela,yVenezuela)));
        SouthAmericaContinent.addLand(LandSprite("Peru", 0, gf::Color::Red, pathPeru, gf::Vector2i(xPeru,yPeru)));
        SouthAmericaContinent.addLand(LandSprite("Brazil", 0, gf::Color::Red, pathBrazil, gf::Vector2i(xBrazil,yBrazil)));
        SouthAmericaContinent.addLand(LandSprite("Argentina", 0, gf::Color::Red, pathArgentina, gf::Vector2i(xArgentina,yArgentina)));
        

        // Europe
        Continent EuropeContinent("Europe", 5);
        //TODO G OUBLIE L'ISLANDE
        EuropeContinent.addLand(LandSprite("Great Britain", 0, gf::Color::Red, pathGB, gf::Vector2i(xGB,yGB)));
        EuropeContinent.addLand(LandSprite("Scandinavia", 0, gf::Color::Red, pathScandinavia, gf::Vector2i(xScandinavia,yScandinavia)));
        EuropeContinent.addLand(LandSprite("Northern Europe", 0, gf::Color::Red, pathEuropeNorth, gf::Vector2i(xEuropeNorth,yEuropeNorth)));
        EuropeContinent.addLand(LandSprite("Southern Europe", 0, gf::Color::Red, pathEuropeSouth, gf::Vector2i(xEuropeSouth,yEuropeSouth)));
        EuropeContinent.addLand(LandSprite("Western Europe", 0, gf::Color::Red, pathEuropeWest, gf::Vector2i(xEuropeWest,yEuropeWest)));
        EuropeContinent.addLand(LandSprite("Eastern Europe", 0, gf::Color::Red, pathEuropeEast, gf::Vector2i(xEuropeEast,yEuropeEast)));
        

        // Africa
        
        Continent AfricaContinent("Africa", 3);
        AfricaContinent.addLand(LandSprite("North Africa", 0, gf::Color::Red, pathNorthAfrica, gf::Vector2i(xNorthAfrica,yNorthAfrica)));
        AfricaContinent.addLand(LandSprite("Egypt", 0, gf::Color::Red, pathEgypte, gf::Vector2i(xEgypte,yEgypte)));
        AfricaContinent.addLand(LandSprite("East Africa", 0, gf::Color::Red, pathEastAfrica, gf::Vector2i(xEastAfrica,yEastAfrica)));
        AfricaContinent.addLand(LandSprite("Congo", 0, gf::Color::Red, pathCongo, gf::Vector2i(xCongo,yCongo)));
        AfricaContinent.addLand(LandSprite("South Africa", 0, gf::Color::Red, pathSouthAfrica, gf::Vector2i(xSouthAfrica,ySouthAfrica)));
        AfricaContinent.addLand(LandSprite("Madagascar", 0, gf::Color::Red, pathMadagascar, gf::Vector2i(xMadagascar,yMadagascar)));
        

        // Asia
        Continent AsiaContinent("Asia", 5);
        
        AsiaContinent.addLand(LandSprite("Ural", 0, gf::Color::Red, pathUral, gf::Vector2i(xUral,yUral)));
        AsiaContinent.addLand(LandSprite("Siberia", 0, gf::Color::Red, pathSiberia, gf::Vector2i(xSiberia,ySiberia)));
        AsiaContinent.addLand(LandSprite("Mongolia", 0, gf::Color::Red, pathMongolia, gf::Vector2i(xMongolia,yMongolia)));
        AsiaContinent.addLand(LandSprite("Japan", 0, gf::Color::Red, pathJapan, gf::Vector2i(xJapan,yJapan)));
        AsiaContinent.addLand(LandSprite("Afghanistan", 0, gf::Color::Red, pathAfhganistan, gf::Vector2i(xAfhganistan,yAfhganistan)));
        AsiaContinent.addLand(LandSprite("China", 0, gf::Color::Red, pathChina, gf::Vector2i(xChina,yChina)));
        AsiaContinent.addLand(LandSprite("Middle East", 0, gf::Color::Red, pathMiddleEast, gf::Vector2i(xMiddleEast,yMiddleEast)));
        AsiaContinent.addLand(LandSprite("India", 0, gf::Color::Red, pathIndia, gf::Vector2i(xIndia,yIndia)));
        

        // Oceania
        
        Continent OceaniaContinent("Oceania", 2);
        OceaniaContinent.addLand(LandSprite("Indonesia", 0, gf::Color::Red, pathIndonesia, gf::Vector2i(xIndonesia,yIndonesia)));
        OceaniaContinent.addLand(LandSprite("New Zealand", 0, gf::Color::Red, pathNewZealand, gf::Vector2i(xNewZealand,yNewZealand)));
        OceaniaContinent.addLand(LandSprite("Western Australia", 0, gf::Color::Red, pathWestAustralia, gf::Vector2i(xWestAustralia,yWestAustralia)));
        OceaniaContinent.addLand(LandSprite("Eastern Australia", 0, gf::Color::Red, pathEastAustralia, gf::Vector2i(xEastAustralia,yEastAustralia)));
        
 */
    }
    void MapEntity::render(gf::RenderTarget& target, const gf::RenderStates& states){
        gf::RenderStates state;
        map.render(target);
    }
}