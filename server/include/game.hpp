#include <vector>
#include "timer.hpp"


struct Player {
    float x = 0;
    float y = 0;
    time_point lastShootTime;
};


struct Missile {
    float x;
    float y;
};


struct GameState {
    Player player;
    std::vector<Missile> missiles;
};