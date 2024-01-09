#include <cstdint>

namespace fisk {
    enum class Type : uint8_t{
        Infantery, // 0
        Cavalry, // 1
        Gunner // 2
    };

    enum class TurnPhase : uint8_t{
        Fortify, // 0
        Attack, // 1
        Reinforce // 2
    };

    enum class GameState : uint8_t{
        Running, // 0
        Paused, // 1
        Stopped // 2
    };
}