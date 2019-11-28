#pragma once
#include "loadTextures.h"
#include "Entity.h"
#include <ctime>
#include <cstdlib>


class Enemy: public Entity
{
private:
    std::vector<sf::IntRect> animation;
    void loadSprite();
public:
    void update();
    sf::Sprite& getSprite();
    Enemy(AppDataRef data, int x, int y);
    ~Enemy(){};
};

