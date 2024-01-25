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