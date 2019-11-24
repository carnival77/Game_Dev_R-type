#include "player.h"
#include "loadTextures.h"


Player::Player()
{
    this->animation = loadPlayerShip();
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && reload > 75){
        shoot = true;
        reload = 0;
    }
    pos = sprite.getPosition();
    return shoot;
}