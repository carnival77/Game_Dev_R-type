#pragma once
#include "App.h"

class Starfield
{
private:
    AppDataRef data;
    std::vector<sf::Sprite> sprites;
public:
    Starfield(AppDataRef data);
    ~Starfield() {};
    void update();
    void draw();
};
