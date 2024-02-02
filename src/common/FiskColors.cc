#include "FiskColors.h"
#include <gf/Vector.h>

namespace fisk {

     LandColor::LandColor(){
        Blue = gf::Color4f({(float)99/255,(float)155/255,(float)255/255,1});
        Orange = gf::Color4f({(float)255/255,(float)140/255,(float)92/255,1});
        Green = gf::Color4f({(float)134/255,(float)192/255,(float)108/255,1});
        Yellow = gf::Color4f({(float)251/255,(float)239/255,(float)8/255,1});
        Neutral = gf::Color4f({(float)48/255,(float)104/255,(float)80/255,1});


        LightBlue = gf::Color::fromRgba32(0x88b3FFFF);
        LightOrange = gf::Color::fromRgba32(0xffab88FF);
        LightGreen = gf::Color::fromRgba32(0x9cc48aFF);
        LightYellow = gf::Color::fromRgba32(0xfff759FF);
        LightNeutral = gf::Color::fromRgba32(0x4a9172FF);


        DarkBlue = gf::Color::fromRgba32(0x2274ffFF);
        DarkOrange = gf::Color::fromRgba32(0xf76326FF);
        DarkGreen = gf::Color::fromRgba32(0x63cc4bFF);
        DarkYellow = gf::Color::fromRgba32(0xd0c600FF);
        DarkNeutral = gf::Color::fromRgba32(0x1a4030FF);
    }

     PlayerColor::PlayerColor()
   : Orange({(float)255/255,(float)140/255,(float)92/255,1})
   , Blue({(float)99/255,(float)155/255,(float)255/255,1})
   , Green({(float)134/255,(float)192/255,(float)108/255,1})
   , Yellow({(float)251/255,(float)239/255,(float)8/255,1})
   , Neutral({(float)48/255,(float)104/255,(float)80/255,1})
   {

   }
    HUDColor::HUDColor(){
        backgroundColor = gf::Color::fromRgb((float)7/255, (float)24/255, (float)33/255);
        buttonColor = gf::Color::fromRgba32(0xE0F8CFFF);
        plotUnfilled = gf::Color::fromRgba32(0x95aa87FF);
        redClose = gf::Color::fromRgba32(0xB32F2FFF);
    }
}
