#include "player.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>


//Color: 0..3 (blue, red, yellow and green)
Player::Player(AppDataRef data,int x, int y, int color)
{
    this->data = data;
    sprite.setPosition(x, y);
    setAnimation(color);
}

void Player::setAnimation(int color)
{
    sprite.setTexture(data->textures.get("Players"));

    sf::Vector2u shapeSize = sprite.getTexture()->getSize();
    shapeSize.x /= 5;
    shapeSize.y /= 5;

    for (int i = 0; i < 5; i++)
    {
        animation.push_back(sf::IntRect(shapeSize.x * i, shapeSize.y * color, shapeSize.x, shapeSize.y));
    }
    sprite.setTextureRect(animation[2]);
    sprite.setScale(3,3);
}

void Player::update()
{
    sprite.setTextureRect(animation[2]);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        network -> write("KEY:LEFT");
        
        std::string reply = network -> extract_payload(network -> read());
        std::vector<std::string> split_vect;
        boost::split(split_vect, reply, boost::is_any_of(":"));
        for (auto e = split_vect.begin(); e != split_vect.end(); e++) {
            std::cout << *e << " ";
        }
        std::cout << "\n";

        // std::vector<std::string> split_vect2;
        boost::split(split_vect, split_vect[1], boost::is_any_of(";"));
        for (auto e = split_vect.begin(); e != split_vect.end(); e++) {
            std::cout << *e << " ";
        }
        std::cout << "\n";

        float x = std::stof(split_vect[0]);
        float y = std::stof(split_vect[1]);

        sprite.setPosition(x, y);
        // sprite.setPosition(sprite.getPosition()+sf::Vector2f(-PLAYER_SPEED,0.0));
        // sprite.move(sf::Vector2f(-PLAYER_SPEED,0.0));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        network -> write("KEY:RIGHT");
        sprite.move(sf::Vector2f(PLAYER_SPEED,0.0));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        network -> write("KEY:UP");
        sprite.setTextureRect(animation[4]);
        sprite.move(sf::Vector2f(0.0,-PLAYER_SPEED));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        network -> write("KEY:DOWN");
        sprite.setTextureRect(animation[0]);
        sprite.move(sf::Vector2f(0.0,PLAYER_SPEED));
    }
}

sf::Sprite& Player::getSprite()
{
    return sprite;
}

Missile Player::shoot()
{
    Missile dummy(data, sprite.getPosition().x + sprite.getTextureRect().width, sprite.getPosition().y + sprite.getTextureRect().height/2);
    return dummy;
}
