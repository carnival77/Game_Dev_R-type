#pragma once
#include "Entity.h"

class Missile: public Entity
{
private:
    void loadSprite();
public:
    void update();
    sf::Sprite& getSprite();
    Missile(AppDataRef data,int x, int y);
    bool isInside(sf::FloatRect rect);
    ~Missile() {};
};
