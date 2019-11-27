#include "enemy.h"
#include <iostream>
Enemy::Enemy(int x, int y)
{
    animation = loadRedShip();
    sprite = animation[0];
    sprite.setPosition(x,y); 
}

Enemy::~Enemy()
{
}

void Enemy::enemyMove()
{
    static int state = 0;
    state++;
    //std::cout << state << "\n";
    //sprite = animation[0];
    //sprite.setPosition(pos);
    sprite.move(sf::Vector2f(-5,0));
}