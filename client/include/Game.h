#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "App.h"

class Game : public cScreen
{
public:
    Game(AppDataRef data);
    ~Game(){};
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadTextures();

    AppDataRef data;
    Player * player;
    vector<Enemy> enemies;
    vector<Missile> missiles;
    sf::Clock clock;
    sf::Sprite background;
};