#pragma once
#include <string>
#include "SFML/Graphics.hpp"


class Background {
    public:
        Background(std::string textureFile);
        ~Background();
        sf::Texture texture;
        sf::Sprite sprite;
};