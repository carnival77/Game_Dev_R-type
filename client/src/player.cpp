#include "player.h"

#include <iostream>
#include <tuple>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include "rtype_common/parsing.hpp"


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


std::tuple<int, float, float, std::string> unpack_player(std::string message) {
    std::vector<std::string> split_vect = rtype_common::split(message, ":");
    split_vect = rtype_common::split(split_vect[1], ";");
    int player_idx = std::stoi(split_vect[0]);
    float x = std::stof(split_vect[1]);
    float y = std::stof(split_vect[2]);
    std::string animation = split_vect[3];
    return std::make_tuple(player_idx, x, y, animation);
}


void Player::update()
{
    sprite.setTextureRect(animation[2]);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
        network -> write("KEY:LEFT");

        // std::string reply = network -> read_payload();
        // std::vector<std::string> split_vect = rtype_common::split(reply, ":");
        // split_vect = rtype_common::split(split_vect[1], ";");
        // rtype_common::print(split_vect);
        
        // std::string reply = network -> read_payload();
        // std::vector<std::string> split_vect = rtype_common::split(reply, ":");
        // split_vect = rtype_common::split(split_vect[1], ";");
        // int player_idx = std::stoi(split_vect[0]);
        // float x = std::stof(split_vect[1]);
        // float y = std::stof(split_vect[2]);
        // std::string animation = split_vect[3];

        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "LEFT") {}

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
        network -> write("KEY:RIGHT");

        // std::string reply = network -> read_payload();
        // std::vector<std::string> split_vect = rtype_common::split(reply, ":");
        // split_vect = rtype_common::split(split_vect[1], ";");
        // rtype_common::print(split_vect);
        // int player_idx = std::stoi(split_vect[0]);
        // std::string key = split_vect[1];
        // if (key == "RIGHT") {
        //     sprite.move(sf::Vector2f(PLAYER_SPEED,0.0));
        // }
        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "RIGHT") {}
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
        network -> write("KEY:UP");

        // std::string reply = network -> read_payload();
        // std::vector<std::string> split_vect = rtype_common::split(reply, ":");
        // split_vect = rtype_common::split(split_vect[1], ";");
        // rtype_common::print(split_vect);
        // int player_idx = std::stoi(split_vect[0]);
        // std::string key = split_vect[1];
        // if (key == "UP") {
        //     sprite.setTextureRect(animation[4]);
        //     sprite.move(sf::Vector2f(0.0,-PLAYER_SPEED));
        // }
        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = unpack_player(message);
        sprite.setPosition(x, y);
        if (animation_type == "UP") {
            sprite.setTextureRect(animation[4]);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
        network -> write("KEY:DOWN");

        // std::string reply = network -> read_payload();
        // std::vector<std::string> split_vect = rtype_common::split(reply, ":");
        // split_vect = rtype_common::split(split_vect[1], ";");
        // rtype_common::print(split_vect);
        // int player_idx = std::stoi(split_vect[0]);
        // std::string key = split_vect[1];

        // if (key == "DOWN") {
        //    sprite.setTextureRect(animation[0]);
        //     sprite.move(sf::Vector2f(0.0,PLAYER_SPEED));
        // }
        std::string message = network -> read_payload();
        auto [player_idx, x, y, animation_type] = unpack_player(message);
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
