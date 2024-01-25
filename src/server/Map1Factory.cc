#include "Map1Factory.h"
#include "GameInstance.h"
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


        LandId Alaska = model->add_land(Land(0, "Alaska", {}, gf::InvalidId));
        model->get_continent(NorthAmerica).add_land(Alaska);
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


        model->get_land(Alaska).addNeighbor(NorthwestTerritory);
        model->get_land(Alaska).addNeighbor(Atlanta);
        //TODO add all neigbors BOTH WAYS :)


        return model;
    }

    Map1Factory::Map1Factory() {
    }

  std::unique_ptr<GameInstance> Map1Factory::createInstance() {
      std::unique_ptr<GameInstance> new_instance(new GameInstance(createModelForMap1()));
      return new_instance;
  }

}
