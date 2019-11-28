#include "missile.h"

Missile::Missile(AppDataRef data, int x, int y)
{
    this->data = data;
    loadSprite();
    sprite.setPosition(x,y);
}

void Missile::update()
{
    sprite.move(8,0);
}

bool Missile::isInside(sf::FloatRect rect)
{
    return sprite.getGlobalBounds().intersects(rect);
}

sf::Sprite& Missile::getSprite()
{
    return sprite;
}

void Missile::loadSprite()
{
    sprite.setTexture(data->textures.get("PlayerMissile"));
    sprite.setTextureRect(sf::IntRect(249, 90, 16, 4));
    sprite.setScale(sf::Vector2f(3,3));
}