#pragma once
#include "App.h"

class Entity
{
public:
    virtual void update() = 0;
    virtual sf::Sprite& getSprite() = 0;
protected:
    AppDataRef data;
    sf::Sprite sprite;
};
