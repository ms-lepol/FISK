#ifndef FISK_COLORS_H
#define FISK_COLORS_H
#include <gf/Vector.h>
#include <gf/Color.h>

namespace fisk {

    struct LandColor {
        LandColor();
        gf::Color4f Blue;
        gf::Color4f Orange;
        gf::Color4f Green;
        gf::Color4f Yellow;
        gf::Color4f Neutral;

        gf::Color4f LightBlue;
        gf::Color4f LightOrange;
        gf::Color4f LightGreen;
        gf::Color4f LightYellow;
        gf::Color4f LightNeutral;

        gf::Color4f DarkBlue;
        gf::Color4f DarkOrange;
        gf::Color4f DarkGreen;
        gf::Color4f DarkYellow;
        gf::Color4f DarkNeutral;
    };

    struct PlayerColor {
        PlayerColor();
        gf::Color4f Blue;
        gf::Color4f Orange;
        gf::Color4f Green;
        gf::Color4f Yellow;
        gf::Color4f Neutral;
    };

    struct HUDColor {
        HUDColor();
        gf::Color4f backgroundColor;
        gf::Color4f buttonColor;
        gf::Color4f plotUnfilled;
        gf::Color4f redClose;
        gf::Color4f greenCheck;
    };
}
#endif // FISK_COLORS_H