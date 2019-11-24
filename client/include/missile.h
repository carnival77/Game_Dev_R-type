#pragma once
#include "loadTextures.h"

class Missile
{
public:
    sf::Vector2f pos;
    sf::Sprite sprite;
    Missile(int x, int y);
    ~Missile();
    bool moveMissile(sf::Vector2u winSize);
};
