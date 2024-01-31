#include "Map1Factory.h"
#include "GameInstance.h"
#include <gf/Log.h>
#include <memory>

namespace fisk {

    std::unique_ptr<Game> createModelForMap1(){
        std::unique_ptr<Game> model(new Game());
        gf::Log::info("here\n");
        ContinentId Europe = model->add_continent(Continent("Europe", {}));
        ContinentId NorthAmerica = model->add_continent(Continent("North America", {}));
        ContinentId SouthAmerica = model->add_continent(Continent("South America", {}));
        ContinentId Asia = model->add_continent(Continent("Asia", {}));
        ContinentId Africa = model->add_continent(Continent("Africa", {}));
        ContinentId Oceania = model->add_continent(Continent("Oceania", {}));

        gf::Log::info("here\n");

        LandId Alaska = model->add_land(Land(0, "Alaska", {}, gf::InvalidId));
        gf::Log::info("here\n");
        model->get_continent(NorthAmerica).add_land(Alaska);
        gf::Log::info("here\n");
        LandId NorthwestTerritory = model->add_land(Land(0, "NorthwestTerritory", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(NorthwestTerritory);
        LandId Greenland = model->add_land(Land(0, "Greenland", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Greenland);
        LandId Atlanta = model->add_land(Land(0, "Atlanta", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Atlanta);
        LandId Ontario = model->add_land(Land(0, "Ontario", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Ontario);
        LandId Quebec = model->add_land(Land(0, "Quebec", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Quebec);
        LandId WesternUnitedStates = model->add_land(Land(0, "WesternUnitedStates", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(WesternUnitedStates);
        LandId EasternUnitedStates = model->add_land(Land(0, "EasternUnitedStates", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(EasternUnitedStates);
        LandId CentralAmerica = model->add_land(Land(0, "CentralAmerica", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(CentralAmerica);
        LandId Venezuela = model->add_land(Land(0, "Venezuela", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Venezuela);
        LandId Peru = model->add_land(Land(0, "Peru", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Peru);
        LandId Brazil = model->add_land(Land(0, "Brazil", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Brazil);
        LandId Argentina = model->add_land(Land(0, "Argentina", {}, gf::InvalidId));
        model->get_continent(SouthAmerica).add_land(Argentina);
        LandId GreatBritain = model->add_land(Land(0, "GreatBritain", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(GreatBritain);
        LandId Scandinavia = model->add_land(Land(0, "Scandinavia", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(Scandinavia);
        LandId NorthernEurope = model->add_land(Land(0, "NorthernEurope", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(NorthernEurope);
        LandId SouthernEurope = model->add_land(Land(0, "SouthernEurope", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(SouthernEurope);
        LandId WesternEurope = model->add_land(Land(0, "WesternEurope", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(WesternEurope);
        LandId EasternEurope = model->add_land(Land(0, "EasternEurope", {}, gf::InvalidId));
        model->get_continent(Europe).add_land(EasternEurope);
        LandId NorthAfrica = model->add_land(Land(0, "NorthAfrica", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(NorthAfrica);
        LandId Egypt = model->add_land(Land(0, "Egypt", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Egypt);
        LandId EastAfrica = model->add_land(Land(0, "EastAfrica", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(EastAfrica);
        LandId Congo = model->add_land(Land(0, "Congo", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Congo);
        LandId SouthAfrica = model->add_land(Land(0, "SouthAfrica", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(SouthAfrica);
        LandId Madagascar = model->add_land(Land(0, "Madagascar", {}, gf::InvalidId));
        model->get_continent(Africa).add_land(Madagascar);
        LandId Ural = model->add_land(Land(0, "Ural", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Ural);
        LandId Siberia = model->add_land(Land(0, "Siberia", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Siberia);
        LandId Mongolia = model->add_land(Land(0, "Mongolia", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Mongolia);
        LandId Japan = model->add_land(Land(0, "Japan", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Japan);
        LandId Afghanistan = model->add_land(Land(0, "Afghanistan", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Afghanistan);
        LandId China = model->add_land(Land(0, "China", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(China);
        LandId MiddleEast = model->add_land(Land(0, "MiddleEast", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(MiddleEast);
        LandId India = model->add_land(Land(0, "India", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(India);
        LandId Indonesia = model->add_land(Land(0, "Indonesia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(Indonesia);
        LandId NewZealand = model->add_land(Land(0, "NewZealand", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(NewZealand);
        LandId WesternAustralia = model->add_land(Land(0, "WesternAustralia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(WesternAustralia);
        LandId EasternAustralia = model->add_land(Land(0, "EasternAustralia", {}, gf::InvalidId));
        model->get_continent(Oceania).add_land(EasternAustralia);
        LandId Thailande = model->add_land(Land(0, "Thailande", {}, gf::InvalidId));
        model->get_continent(Asia).add_land(Thailande);

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

        model->get_land(Quebec).addNeighbor(Greenland);
        model->get_land(Quebec).addNeighbor(Ontario);
        model->get_land(Quebec).addNeighbor(EasternUnitedStates);

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
        model->get_land(NorthernEurope).addNeighbor(Scandinavia);

        model->get_land(SouthernEurope).addNeighbor(WesternEurope);
        model->get_land(SouthernEurope).addNeighbor(NorthernEurope);
        model->get_land(SouthernEurope).addNeighbor(EasternEurope);
        model->get_land(SouthernEurope).addNeighbor(Egypt);

        model->get_land(WesternEurope).addNeighbor(GreatBritain);
        model->get_land(WesternEurope).addNeighbor(NorthernEurope);
        model->get_land(WesternEurope).addNeighbor(SouthernEurope);
        model->get_land(WesternEurope).addNeighbor(NorthAfrica);

        model->get_land(EasternEurope).addNeighbor(Scandinavia);
        model->get_land(EasternEurope).addNeighbor(NorthernEurope);
        model->get_land(EasternEurope).addNeighbor(SouthernEurope);
        model->get_land(EasternEurope).addNeighbor(Afghanistan);

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

        model->get_land(Mongolia).addNeighbor(Siberia);
        model->get_land(Mongolia).addNeighbor(China);
        model->get_land(Mongolia).addNeighbor(Japan);
        model->get_land(Mongolia).addNeighbor(Afghanistan);

        model->get_land(Japan).addNeighbor(Mongolia);
        model->get_land(Japan).addNeighbor(China);

        model->get_land(Afghanistan).addNeighbor(Ural);
        model->get_land(Afghanistan).addNeighbor(Mongolia);
        model->get_land(Afghanistan).addNeighbor(China);
        model->get_land(Afghanistan).addNeighbor(MiddleEast);


        model->get_land(China).addNeighbor(Siberia);
        model->get_land(China).addNeighbor(Mongolia);
        model->get_land(China).addNeighbor(Afghanistan);
        model->get_land(China).addNeighbor(India);
        model->get_land(China).addNeighbor(Thailande);

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

        model->get_land(WesternAustralia).addNeighbor(Indonesia);
        model->get_land(WesternAustralia).addNeighbor(NewZealand);
        model->get_land(WesternAustralia).addNeighbor(EasternAustralia);

        model->get_land(EasternAustralia).addNeighbor(WesternAustralia);
        model->get_land(EasternAustralia).addNeighbor(NewZealand);

        model->get_land(Thailande).addNeighbor(India);
        model->get_land(Thailande).addNeighbor(China);
        model->get_land(Thailande).addNeighbor(Indonesia);
        

        
        //Checks if the neighbors are correct
        if (!model->is_neighbours_correct()) {
            gf::Log::warning("The neighbors are not correct\n");
        } else {
            gf::Log::info("The neighbors are correct\n");
        }

        return model;
    }

    Map1Factory::Map1Factory() {
    }

  std::unique_ptr<GameInstance> Map1Factory::createInstance() {
      std::unique_ptr<GameInstance> new_instance(new GameInstance(createModelForMap1()));
      return new_instance;
  }

}
