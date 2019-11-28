#include "enemy.h"

Enemy::Enemy(AppDataRef data, int x, int y)
{
    this->data = data;
    loadSprite();
    sprite.setPosition(x,y); 
}

void Enemy::update()
{
    sprite.move(sf::Vector2f(-ENEMY_SPEED,0));
}

sf::Sprite& Enemy::getSprite()
{
    return sprite;
}

void Enemy::loadSprite()
{
    sprite.setTexture(data->textures.get("RedPlane"));
    sf::Vector2u shapeSize = sprite.getTexture()->getSize();
    shapeSize.x /= 16;
    for (int i = 0; i < 4; i++)
    {
        animation.push_back(sf::IntRect(shapeSize.x * i, 6, shapeSize.x, shapeSize.y - 12));
    }
    sprite.setScale(3,3);
    sprite.setTextureRect(animation[0]);
}