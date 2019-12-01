#include "player.h"

#include <iostream>
#include "rtype_common/protocol.hpp"


//Color: 0..3 (blue, red, yellow and green)
Player::Player(AppDataRef data,int x, int y, int color)
{
    this->data = data;
    sprite.setPosition(x, y);
    setAnimation(color);

    // std::cout << "width: " << sprite.getTextureRect().width << "\n";
    // std::cout << "height: " << sprite.getTextureRect().height << "\n";
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

        std::string message = network -> read_payload();
        // C++ 17 structured binding
        auto [player_idx, x, y, animation_type] = rtype_common::unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "LEFT") {}

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        network -> write("KEY:RIGHT");

        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = rtype_common::unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "RIGHT") {}
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        network -> write("KEY:UP");

        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = rtype_common::unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "UP") {
            sprite.setTextureRect(animation[4]);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        network -> write("KEY:DOWN");

        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = rtype_common::unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "DOWN") {
            sprite.setTextureRect(animation[0]);
        }

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
