#include "missile.h"

Missile::Missile(int x, int y)
{
    sprite = loadPlayerMissile();
    sprite.setPosition(x,y);
}

Missile::~Missile()
{
}

bool Missile::moveMissile(sf::Vector2u winSize)
{
    sprite.move(8,0);
    if(sprite.getPosition().x > winSize.x || sprite.getPosition().x < 0)
    {
        return false;
    }
    if(sprite.getPosition().y > winSize.y || sprite.getPosition().y < 0)
    {
        return false;
    }
    return true;
}
