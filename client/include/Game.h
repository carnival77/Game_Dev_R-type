#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "background.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Player player;
    Background background;
    vector<Enemy> enemies;
    vector<Missile> missiles;
};