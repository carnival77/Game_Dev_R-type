#pragma once
#include "entity.h"
#include <vector>

class Player
{
private:
    std::vector<sf::Sprite> animation;
public:
    sf::Vector2f pos;
    sf::Sprite sprite;
    Player();
    ~Player();
    bool movePlayer(float speed);
};
