#include <vector>


struct Player {
    float x = 0;
    float y = 0;
};


struct Missile {
    float x;
    float y;
};


struct GameState {
    Player player;
    std::vector<Missile> missiles;
};