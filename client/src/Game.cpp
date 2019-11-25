#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode::getDesktopMode(), "Client Rtype", sf::Style::Close),
               background("./textures/background.jpg")
{
    //window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}

void Game::update()
{
    static int generator = 0;
    static const int power = 120; 
    generator++;
    if(generator > power)//New Enemy
    {
        generator = 0;
        Enemy enemy(window.getSize().x, (rand() % (window.getSize().y - 300) +100));
        enemies.push_back(enemy);
    }

    //Update enemies
    for (size_t i = 0; i < enemies.size(); i++)
    {
        enemies[i].enemyMove();
        if(enemies[i].sprite.getPosition().x < 0)
        {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
    //Player shooting mechanic
    static const float speed = 0.7;
    if(player.movePlayer(speed))
    {
        Missile dummy(player.sprite.getPosition().x + 50 , player.sprite.getPosition().y);
        missiles.push_back(dummy);
    }
    //Update missiles and check collisions
    for (size_t i = 0; i < missiles.size(); i++) //Move Missile
    {
        if(!missiles[i].moveMissile(window.getSize()))
        {
            missiles.erase(missiles.begin() + i);
            i--;
            continue;
        }
        for (size_t j = 0; j < enemies.size(); j++)
        {
            if(missiles[i].sprite.getGlobalBounds().intersects(enemies[j].sprite.getGlobalBounds()))
            {
                missiles.erase(missiles.begin() + i);
                enemies.erase(enemies.begin() + j);
                i--;
                break;
            }
        }
    }
    //Check player collisions
    sf::FloatRect playerBox = player.sprite.getGlobalBounds();
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if(playerBox.intersects(enemies[i].sprite.getGlobalBounds()))
        {
            std::cout << "You are dead!!\n";
            window.close();
        }
    }
    

}

void Game::render()
{
    window.clear(sf::Color(66, 66, 132, 255));

    window.draw(background.sprite);
    
    //draw()
    //Draw enemies
    for (size_t i = 0; i < enemies.size(); i++) window.draw(enemies[i].sprite);
    //Draw missiles
    for (size_t i = 0; i < missiles.size(); i++) window.draw(missiles[i].sprite);
    //Draw player
    window.draw(player.sprite);

    window.display();
}