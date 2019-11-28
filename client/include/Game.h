#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "background.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "cScreen.h"
<<<<<<< HEAD
using boost::asio::ip::udp;
=======
#include "cTexture.h"
#include "network.hpp"
>>>>>>> 98caf0a4099d35e9b9a8ebb4170077bdd9a17e27

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

    // Network network;
};