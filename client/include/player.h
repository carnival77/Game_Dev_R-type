#pragma once
#include <vector>
#include "cTexture.h"
#include "Entity.h"
#include "missile.h"
#include "network.hpp"


class Player: public Entity
{
private:
    std::vector<sf::IntRect> animation;
    void setAnimation(int color);

public:
    Player(AppDataRef data,int x, int y, int color);
    ~Player(){};
    void update();
    sf::Sprite& getSprite();
    Missile shoot();
    Network * network;
};
