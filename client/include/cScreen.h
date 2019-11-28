#pragma once
#include <SFML/Graphics.hpp>

class cScreen
{
public:
    virtual void run() = 0;
    virtual void processEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};