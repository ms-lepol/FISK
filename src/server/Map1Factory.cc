#include "Map1Factory.h"
#include "GameInstance.h"
#include <gf/Log.h>
#include <gf/Random.h>
#include <memory>

namespace fisk {

    std::unique_ptr<Game> createModelForMap1(){
        std::unique_ptr<Game> model(new Game());
        ContinentId Europe = model->add_continent(Continent("Europe", {}));
        ContinentId NorthAmerica = model->add_continent(Continent("North America", {}));
        ContinentId SouthAmerica = model->add_continent(Continent("South America", {}));
        ContinentId Asia = model->add_continent(Continent("Asia", {}));
        ContinentId Africa = model->add_continent(Continent("Africa", {}));
        ContinentId Oceania = model->add_continent(Continent("Oceania", {}));


        LandId Alaska = model->add_land(Land(1, "Alaska", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Alaska);
        LandId NorthwestTerritory = model->add_land(Land(1, "Northwest Territory", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(NorthwestTerritory);
        LandId Greenland = model->add_land(Land(1, "Greenland", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Greenland);
        LandId Atlanta = model->add_land(Land(1, "Atlanta", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Atlanta);
        LandId Ontario = model->add_land(Land(1, "Ontario", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Ontario);
        LandId Quebec = model->add_land(Land(1, "Quebec", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Quebec);
        LandId WesternUnitedStates = model->add_land(Land(1, "Western United States", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(WesternUnitedStates);
        LandId EasternUnitedStates = model->add_land(Land(1, "Eastern United States", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(EasternUnitedStates);
        LandId CentralAmerica = model->add_land(Land(1, "Central America", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(CentralAmerica);
        LandId Venezuela = model->add_land(Land(1, "Venezuela", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Venezuela);
        LandId Peru = model->add_land(Land(1, "Peru", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Peru);
        LandId Brazil = model->add_land(Land(1, "Brazil", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Brazil);
        LandId Argentina = model->add_land(Land(1, "Argentina", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Argentina);
        LandId GreatBritain = model->add_land(Land(1, "Great Britain", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(GreatBritain);
        LandId Scandinavia = model->add_land(Land(1, "Scandinavia", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(Scandinavia);
        LandId NorthernEurope = model->add_land(Land(1, "Northern Europe", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(NorthernEurope);
        LandId SouthernEurope = model->add_land(Land(1, "Southern Europe", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(SouthernEurope);
        LandId WesternEurope = model->add_land(Land(1, "Western Europe", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(WesternEurope);
        LandId EasternEurope = model->add_land(Land(1, "Eastern Europe", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(EasternEurope);
        LandId NorthAfrica = model->add_land(Land(1, "North Africa", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(NorthAfrica);
        LandId Egypt = model->add_land(Land(1, "Egypt", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Egypt);
        LandId EastAfrica = model->add_land(Land(1, "East Africa", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(EastAfrica);
        LandId Congo = model->add_land(Land(1, "Congo", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Congo);
        LandId SouthAfrica = model->add_land(Land(1, "South Africa", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(SouthAfrica);
        LandId Madagascar = model->add_land(Land(1, "Madagascar", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Madagascar);
        LandId Ural = model->add_land(Land(1, "Ural", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Ural);
        LandId Siberia = model->add_land(Land(1, "Siberia", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Siberia);
        LandId Mongolia = model->add_land(Land(1, "Mongolia", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Mongolia);
        LandId Japan = model->add_land(Land(1, "Japan", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Japan);
        LandId Afghanistan = model->add_land(Land(1, "Afghanistan", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Afghanistan);
        LandId China = model->add_land(Land(1, "China", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(China);
        LandId MiddleEast = model->add_land(Land(1, "Middle East", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(MiddleEast);
        LandId India = model->add_land(Land(1, "India", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(India);
        LandId Indonesia = model->add_land(Land(1, "Indonesia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(Indonesia);
        LandId NewZealand = model->add_land(Land(1, "New Zealand", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(NewZealand);
        LandId WesternAustralia = model->add_land(Land(1, "Western Australia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(WesternAustralia);
        LandId EasternAustralia = model->add_land(Land(1, "Eastern Australia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(EasternAustralia);
        LandId Thailande = model->add_land(Land(1, "Thailande", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Thailande);

        //gf::Log::debug("here\n");
        model->get_land(Alaska).addNeighbor(NorthwestTerritory);
        model->get_land(Alaska).addNeighbor(Atlanta);
        model->get_land(Alaska).addNeighbor(Mongolia);


        model->get_land(NorthwestTerritory).addNeighbor(Alaska);
        model->get_land(NorthwestTerritory).addNeighbor(Greenland);
        model->get_land(NorthwestTerritory).addNeighbor(Ontario);
        model->get_land(NorthwestTerritory).addNeighbor(Atlanta);
        model->get_land(NorthwestTerritory).addNeighbor(Quebec);

        model->get_land(Greenland).addNeighbor(NorthwestTerritory);
        model->get_land(Greenland).addNeighbor(Quebec);
        model->get_land(Greenland).addNeighbor(GreatBritain);
        model->get_land(Greenland).addNeighbor(Ontario);
        

        model->get_land(Atlanta).addNeighbor(Alaska);
        model->get_land(Atlanta).addNeighbor(NorthwestTerritory);
        model->get_land(Atlanta).addNeighbor(Ontario);
        model->get_land(Atlanta).addNeighbor(WesternUnitedStates);

        model->get_land(Ontario).addNeighbor(NorthwestTerritory);
        model->get_land(Ontario).addNeighbor(Greenland);
        model->get_land(Ontario).addNeighbor(Quebec);
        model->get_land(Ontario).addNeighbor(WesternUnitedStates);
        model->get_land(Ontario).addNeighbor(EasternUnitedStates);
        model->get_land(Ontario).addNeighbor(Atlanta);

       
        model->get_land(Quebec).addNeighbor(EasternUnitedStates);
        model->get_land(Quebec).addNeighbor(NorthwestTerritory);
        model->get_land(Quebec).addNeighbor(Greenland);
        model->get_land(Quebec).addNeighbor(Ontario);

        model->get_land(WesternUnitedStates).addNeighbor(Atlanta);
        model->get_land(WesternUnitedStates).addNeighbor(Ontario);
        model->get_land(WesternUnitedStates).addNeighbor(EasternUnitedStates);
        model->get_land(WesternUnitedStates).addNeighbor(CentralAmerica);

        model->get_land(EasternUnitedStates).addNeighbor(Ontario);
        model->get_land(EasternUnitedStates).addNeighbor(Quebec);
        model->get_land(EasternUnitedStates).addNeighbor(WesternUnitedStates);   
        model->get_land(EasternUnitedStates).addNeighbor(CentralAmerica);

        model->get_land(CentralAmerica).addNeighbor(WesternUnitedStates);
        model->get_land(CentralAmerica).addNeighbor(EasternUnitedStates);
        model->get_land(CentralAmerica).addNeighbor(Venezuela);

        model->get_land(Venezuela).addNeighbor(CentralAmerica);
        model->get_land(Venezuela).addNeighbor(Peru);
        model->get_land(Venezuela).addNeighbor(Brazil);

        model->get_land(Peru).addNeighbor(Venezuela);
        model->get_land(Peru).addNeighbor(Brazil);
        model->get_land(Peru).addNeighbor(Argentina);

        model->get_land(Brazil).addNeighbor(Venezuela);
        model->get_land(Brazil).addNeighbor(Peru);
        model->get_land(Brazil).addNeighbor(Argentina);
        model->get_land(Brazil).addNeighbor(NorthAfrica);

        model->get_land(Argentina).addNeighbor(Peru);
        model->get_land(Argentina).addNeighbor(Brazil);

        model->get_land(GreatBritain).addNeighbor(Greenland);
        model->get_land(GreatBritain).addNeighbor(WesternEurope);
        model->get_land(GreatBritain).addNeighbor(NorthernEurope);

        
        model->get_land(Scandinavia).addNeighbor(NorthernEurope);
        model->get_land(Scandinavia).addNeighbor(EasternEurope);

        model->get_land(NorthernEurope).addNeighbor(GreatBritain);
        model->get_land(NorthernEurope).addNeighbor(WesternEurope);
        model->get_land(NorthernEurope).addNeighbor(SouthernEurope);
        model->get_land(NorthernEurope).addNeighbor(EasternEurope);
        model->get_land(NorthernEurope).addNeighbor(Scandinavia);

        model->get_land(SouthernEurope).addNeighbor(WesternEurope);
        model->get_land(SouthernEurope).addNeighbor(NorthernEurope);
        model->get_land(SouthernEurope).addNeighbor(EasternEurope);
        model->get_land(SouthernEurope).addNeighbor(Egypt);
        model->get_land(SouthernEurope).addNeighbor(MiddleEast);

        model->get_land(WesternEurope).addNeighbor(GreatBritain);
        model->get_land(WesternEurope).addNeighbor(NorthernEurope);
        model->get_land(WesternEurope).addNeighbor(SouthernEurope);
        model->get_land(WesternEurope).addNeighbor(NorthAfrica);

        model->get_land(EasternEurope).addNeighbor(Scandinavia);
        model->get_land(EasternEurope).addNeighbor(NorthernEurope);
        model->get_land(EasternEurope).addNeighbor(SouthernEurope);
        model->get_land(EasternEurope).addNeighbor(Afghanistan);
         model->get_land(EasternEurope).addNeighbor(MiddleEast);

        model->get_land(NorthAfrica).addNeighbor(Brazil);
        model->get_land(NorthAfrica).addNeighbor(WesternEurope);
        model->get_land(NorthAfrica).addNeighbor(Egypt);
        model->get_land(NorthAfrica).addNeighbor(EastAfrica);
        model->get_land(NorthAfrica).addNeighbor(Congo);

        model->get_land(Egypt).addNeighbor(NorthAfrica);
        model->get_land(Egypt).addNeighbor(SouthernEurope);
        model->get_land(Egypt).addNeighbor(EastAfrica);
        model->get_land(Egypt).addNeighbor(MiddleEast);

        model->get_land(EastAfrica).addNeighbor(NorthAfrica);
        model->get_land(EastAfrica).addNeighbor(Egypt);
        model->get_land(EastAfrica).addNeighbor(Congo);
        model->get_land(EastAfrica).addNeighbor(MiddleEast);
        model->get_land(EastAfrica).addNeighbor(Madagascar);
        model->get_land(EastAfrica).addNeighbor(SouthAfrica);

        model->get_land(Congo).addNeighbor(NorthAfrica);
        model->get_land(Congo).addNeighbor(EastAfrica);
        model->get_land(Congo).addNeighbor(SouthAfrica);

        model->get_land(SouthAfrica).addNeighbor(EastAfrica);
        model->get_land(SouthAfrica).addNeighbor(Congo);
        model->get_land(SouthAfrica).addNeighbor(Madagascar);

        model->get_land(Madagascar).addNeighbor(EastAfrica);
        model->get_land(Madagascar).addNeighbor(SouthAfrica);

        model->get_land(Ural).addNeighbor(Siberia);
        model->get_land(Ural).addNeighbor(Afghanistan);

        model->get_land(Siberia).addNeighbor(Ural);
        model->get_land(Siberia).addNeighbor(Mongolia);
        model->get_land(Siberia).addNeighbor(China);
        model->get_land(Siberia).addNeighbor(Afghanistan);

        model->get_land(Mongolia).addNeighbor(Siberia);
        model->get_land(Mongolia).addNeighbor(China);
        model->get_land(Mongolia).addNeighbor(Japan);
        model->get_land(Mongolia).addNeighbor(Alaska);
        

        model->get_land(Japan).addNeighbor(Mongolia);
        model->get_land(Japan).addNeighbor(China);

        model->get_land(Afghanistan).addNeighbor(Ural);
        model->get_land(Afghanistan).addNeighbor(Siberia);
        model->get_land(Afghanistan).addNeighbor(India);
        model->get_land(Afghanistan).addNeighbor(MiddleEast);
        model->get_land(Afghanistan).addNeighbor(EasternEurope);


        model->get_land(China).addNeighbor(Siberia);
        model->get_land(China).addNeighbor(Mongolia);
        model->get_land(China).addNeighbor(India);
        model->get_land(China).addNeighbor(Thailande);
        model->get_land(China).addNeighbor(Japan);

        model->get_land(MiddleEast).addNeighbor(Egypt);
        model->get_land(MiddleEast).addNeighbor(EastAfrica);
        model->get_land(MiddleEast).addNeighbor(Afghanistan);
        model->get_land(MiddleEast).addNeighbor(India);
        model->get_land(MiddleEast).addNeighbor(SouthernEurope);
        model->get_land(MiddleEast).addNeighbor(EasternEurope);

        model->get_land(India).addNeighbor(MiddleEast);
        model->get_land(India).addNeighbor(China);
        model->get_land(India).addNeighbor(Thailande);
        model->get_land(India).addNeighbor(Afghanistan);

        model->get_land(Indonesia).addNeighbor(Thailande);
        model->get_land(Indonesia).addNeighbor(NewZealand);
        model->get_land(Indonesia).addNeighbor(WesternAustralia);

        model->get_land(NewZealand).addNeighbor(Indonesia);
        model->get_land(NewZealand).addNeighbor(WesternAustralia);
        model->get_land(NewZealand).addNeighbor(EasternAustralia);

        model->get_land(WesternAustralia).addNeighbor(Indonesia);
        model->get_land(WesternAustralia).addNeighbor(NewZealand);
        model->get_land(WesternAustralia).addNeighbor(EasternAustralia);

        model->get_land(EasternAustralia).addNeighbor(WesternAustralia);
        model->get_land(EasternAustralia).addNeighbor(NewZealand);

        model->get_land(Thailande).addNeighbor(India);
        model->get_land(Thailande).addNeighbor(China);
        model->get_land(Thailande).addNeighbor(Indonesia);
        
        //Checks if the neighbors are correct
        if (model->is_neighbours_correct()) {
            gf::Log::info("(GAME) The neighbors are correct\n");
        } else {
            gf::Log::warning("(GAME) The neighbors are not correct\n");
        }

        //Initialize cards
        for (int i = 1;i<model->get_nb_lands()+1;i++){
            fisk::Type type;
            if (i%3 == 0){
                type = fisk::Type::Infantery;
            }
            else if (i%3 == 1){
                type = fisk::Type::Cavalry;
            }
            else {
                type = fisk::Type::Gunner;
            }
            Card card(type,i);
            model->add_card(card);
        }
        
        Card joker1(fisk::Type::Joker, 0);
        model->add_card(joker1);
        Card joker2(fisk::Type::Joker, 0);
        model->add_card(joker2);

        model->shuffle_cards();
        
        return model;
    }

    Map1Factory::Map1Factory()
    {
    }

    std::unique_ptr<GameInstance> Map1Factory::createInstance(gf::Random& random) {
        std::unique_ptr<GameInstance> new_instance(new GameInstance(createModelForMap1(), random));
        return new_instance;
    }

}
