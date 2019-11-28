#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "background.h"
#include "cScreen.h"
#include "cTexture.h"
#include "network.hpp"

class Game : public cScreen
{
public:
    Game(std::string hostname, unsigned short port);
    virtual int run(sf::RenderWindow &window);

private:
    int processEvents(sf::RenderWindow &window);
    int update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
    void loadTextures();

    Player player;
    //Background background;
    vector<Enemy> enemies;
    vector<Missile> missiles;
    sf::Sprite background;

    cTexture textures;

    Network network;
};