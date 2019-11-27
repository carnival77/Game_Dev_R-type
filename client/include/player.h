#pragma once
#include <vector>
#include "cTexture.h"

class Player
{
private:
    std::vector<sf::Sprite> animation;
public:
    sf::Vector2f pos;
    sf::Sprite sprite;
    Player();
    void setAnimation(cTexture &textures, int color);
    ~Player();
    bool movePlayer(float speed);
};
