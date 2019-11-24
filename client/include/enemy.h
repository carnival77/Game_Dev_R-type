#pragma once
#include "loadTextures.h"
#include <ctime>
#include <cstdlib>


class Enemy
{
private:
    std::vector<sf::Sprite> animation;
public:
    sf::Vector2f pos;
    sf::Sprite sprite;
    Enemy(int x, int y);
    ~Enemy();
    void enemyMove();
};

