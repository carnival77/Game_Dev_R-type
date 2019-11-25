#include <iostream>
#include "Game.h"

// float getDistance(sf::Vector2f fst, sf::Vector2f snd)
// {
//     const float x_diff = fst.x - snd.x;
//     const float y_diff = fst.y - snd.y;
//     return std::sqrt(x_diff * x_diff + y_diff * y_diff);
// }


int main()
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator
    Game game;
    game.run();
    return 0;
}