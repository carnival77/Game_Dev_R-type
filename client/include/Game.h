#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "background.h"
#include <boost/asio.hpp>
#include "cScreen.h"

class Game : public cScreen
{
public:
    Game();
    virtual int run(sf::RenderWindow &window);

private:
    int processEvents(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

    Player player;
    Background background;
    vector<Enemy> enemies;
    vector<Missile> missiles;

    sf::Clock clock;
    sf::Time time;
};