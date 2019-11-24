#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class entity
{
public:
    virtual bool move() = 0;
   
    sf::Vector2f pos;
    sf::Sprite sprite;
};
