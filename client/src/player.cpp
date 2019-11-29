#include "player.h"
#include <iostream>

//Color: 0..3 (blue, red, yellow and green)
Player::Player()
{
}

void Player::setAnimation(cTexture &textures, int color)
{
    sf::Sprite sprite;
    sprite.setTexture(textures.get("Players"));

    sf::Vector2u shapeSize = sprite.getTexture()->getSize();
    shapeSize.x /= 5;
    shapeSize.y /= 5;

    for (int i = 0; i < 5; i++)
    {
        sprite.setTextureRect(sf::IntRect(shapeSize.x * i, shapeSize.y * color, shapeSize.x, shapeSize.y-1));
        sprite.setScale(sf::Vector2f(3,3));
        animation.push_back(sprite);
    }
}


Player::~Player()
{
    
}

bool Player::movePlayer(float speed)
{
    static int reload = 0;
    reload++;
    bool shoot = false;
    sprite = animation[2];
    sprite.setPosition(pos);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        network -> write("KEY: LEFT");
        sprite = animation[2];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(-speed,0.0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        network -> write("KEY: RIGHT");
        sprite = animation[2];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(speed,0.0));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        network -> write("KEY: UP");
        sprite = animation[4];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(0.0,-speed));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        network -> write("KEY: DOWN");
        sprite = animation[0];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(0.0,speed));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && reload > 30){
        // TODO: reload validation on the server-side (to avoid cheating on the client-side)
        network -> write("KEY: SPACE");
        shoot = true;
        reload = 0;
    }
    pos = sprite.getPosition();
    return shoot;
}