#include "Game.h"
#include <iostream>
#include <string>
#include "rtype_common/parsing.hpp"
#include "rtype_common/protocol.hpp"


#define SERVER


Game::Game(AppDataRef data,std::string hostname, unsigned short port)
: network(hostname, port)
{
    this->data = data;
    loadTextures();

    //
	// establish connection with server
    //
    #ifdef SERVER
	network.write("HELLO");
    if (network.read_payload() != "OK") {
        std::cerr << "Could not connect to server.\n";
    } else {
        std::cout << "Connected to server.\n";
    }
    #endif

    loadTextures();
    background.setTexture(data->textures.get("GameBackground"));
    player = new Player(data, 0, 0, 4);
    player -> network = &network;
    starfield = new Starfield(data);
}

void Game::loadTextures()
{
    data->textures.load("Players", "./textures/players.gif");
    data->textures.load("PlayerMissile", "./textures/playerMissiles.gif");
    data->textures.load("RedPlane", "./textures/redEnemyShip.gif");
    data->textures.load("GameBackground", "./textures/gameBackground.png");
}


void Game::run()
{
    processEvents();
    render();
    update();
}

void Game::processEvents()
{
    sf::Event event;
    while (data->window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            data->window.close();
            break;
        // case sf::Event::KeyPressed:
        //     switch (event.key.code)
        //     {
        //         case sf::Keyboard::Escape:
        //             return 1;
        //             break;
        //     }
        }
    }
}

void Game::update()
{
    static float enemySpawn = clock.getElapsedTime().asSeconds();
    static float playerShoot = clock.getElapsedTime().asSeconds();

    //Move the player
    player->update();
    //Move the background
    starfield->update();

    //New Enemy
    if((clock.getElapsedTime().asSeconds() - enemySpawn) >= ENEMY_SPAWN)
    {
        int border = 200;
        enemySpawn = clock.getElapsedTime().asSeconds();
        int enemyH = (rand() % (sHeight - border * 2) + border);
        Enemy enemy(data, sWidth + 100, enemyH);
        enemies.push_back(enemy);
    }

    //Update enemies
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].update();
        if(enemies[i].getSprite().getPosition().x < 0)
        {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }

    //Player shooting mechanic
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        if ((clock.getElapsedTime().asSeconds() - playerShoot) >= PLAYER_RELOAD)
        {
            network.write("KEY:SPACE");
            std::string message = network.read_payload();
            if (rtype_common::starts_with(message, "MISSILE_NEW")) {
                auto [x, y] = rtype_common::unpack_missile_new(message);
                Missile new_missile(data, x, y);
                missiles.push_back(new_missile);
            }
            
            // missiles.push_back(player->shoot());  
            playerShoot = clock.getElapsedTime().asSeconds();
        }      
    }

    //Update missiles and check collisions
    sf::FloatRect windowRect(0,0,data->window.getSize().x,data->window.getSize().y);
    for (size_t i = 0; i < missiles.size(); i++) //Move Missile
    {
        missiles[i].update();
        if(!missiles[i].isInside(windowRect))
        {
            missiles.erase(missiles.begin() + i);
            i--;
            continue;
        }
        for (size_t j = 0; j < enemies.size(); j++)
        {
            if(missiles[i].isInside(enemies[j].getSprite().getGlobalBounds()))
            {
                missiles.erase(missiles.begin() + i);
                enemies.erase(enemies.begin() + j);
                i--;
                break;
            }
        }
    }
    //Check player collisions
    sf::FloatRect playerBox = player->getSprite().getGlobalBounds();
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if(playerBox.intersects(enemies[i].getSprite().getGlobalBounds()))
        {
            std::cout << "You are dead!!\n";
            data->window.close();
            //TODO: add game over screen
        }
    }
}

void Game::render()
{
    data->window.clear();
    starfield->draw();
    //data->window.draw(background);
    
    //draw()
    //Draw enemies
    for (size_t i = 0; i < enemies.size(); i++) 
    {
        data->window.draw(enemies[i].getSprite());
    }
    //Draw missiles
    for (size_t i = 0; i < missiles.size(); i++)
    { 
        data->window.draw(missiles[i].getSprite());
    }
    //Draw player
    data->window.draw(player->getSprite());
    // sf::FloatRect dummy = player.sprite.getGlobalBounds();
    // sf::RectangleShape dummy2(sf::Vector2f(dummy.width, dummy.height));
    // dummy2.setOutlineThickness(2);
    // dummy2.setOutlineColor(sf::Color::Red);
    // dummy2.setFillColor(sf::Color(0,0,0,0));
    // dummy2.setPosition(player.sprite.getPosition());
    // data->window.draw(dummy2);
    data->window.display();
}
