#include "player.h"

//Color: 0..3 (blue, red, yellow and green)
Player::Player()
{
}

void Player::setAnimation(cTexture &textures, int color)
{
    sf::Sprite sprite;
    sprite.setTexture(textures.get(Textures::Players));

    sf::Vector2u shapeSize = sprite.getTexture()->getSize();
    shapeSize.x /= 5;
    shapeSize.y /= 5;

    for (int i = 0; i < 5; i++)
    {
        sprite.setTextureRect(sf::IntRect(shapeSize.x * i, shapeSize.y * color, shapeSize.x, shapeSize.y));
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
        sprite = animation[2];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(-speed,0.0));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        sprite = animation[2];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(speed,0.0));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        sprite = animation[4];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(0.0,-speed));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        sprite = animation[0];
        sprite.setPosition(pos);
        sprite.move(sf::Vector2f(0.0,speed));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && reload > 30){
        shoot = true;
        reload = 0;
    }
    pos = sprite.getPosition();
    return shoot;
}