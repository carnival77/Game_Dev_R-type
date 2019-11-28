#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "cScreen.h"
#include "cTexture.h"
#include "network.hpp"
#include "App.h"

class Game : public cScreen
{
public:
    Game(AppDataRef data, std::string hostname, unsigned short port);
    ~Game(){};
    void run();

private:
    void processEvents();
    void update();
    void render();
    void loadTextures();

    AppDataRef data;
    Player player;
    vector<Enemy> enemies;
    vector<Missile> missiles;
    sf::Sprite background;

    Network network;
};