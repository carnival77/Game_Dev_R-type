#pragma once
#include <SFML/Graphics.hpp>

class cScreen
{
public :
    virtual int run(sf::RenderWindow &app) = 0;
};