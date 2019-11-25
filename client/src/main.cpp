#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include <cmath>

float getDistance(sf::Vector2f fst, sf::Vector2f snd)
{
    const float x_diff = fst.x - snd.x;
    const float y_diff = fst.y - snd.y;
    return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}


int main()
{
    srand(time(NULL));  // initialise seed for random number generator
    std::cout << "I'm the client\n";
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Client Window", sf::Style::Close);
    sf::Event evnt;
    int i = 0;
    float speed = 0.7;
    Player player;
    vector<Enemy> enemies;
    vector<Missile> missiles;
    int generator = 0;
    int power = 120;
    while (window.isOpen())
    {
        while (window.pollEvent(evnt)) //CLose button
        {
            if(evnt.type == evnt.Closed)
                window.close();
        }
        window.clear();
        generator++;
        if(generator > power)//New Enemy
        {
            generator = 0;
            Enemy enemy(window.getSize().x, (rand() % (window.getSize().y - 300) +100));
            enemies.push_back(enemy);
        }
        for (size_t i = 0; i < enemies.size(); i++) //Draw Enemies
        {
            enemies[i].enemyMove();
            window.draw(enemies[i].sprite);
        }
        for (size_t i = 0; i < enemies.size(); i++)//Delete enemies end of screen
        {
            if(enemies[i].sprite.getPosition().x < 0)
                enemies.erase(enemies.begin() + i);
        }
        
        if(player.movePlayer(speed)) //Create missile
        {
            Missile dummy(player.sprite.getPosition().x + 50 , player.sprite.getPosition().y);
            missiles.push_back(dummy);
        }
        for (size_t i = 0; i < missiles.size(); i++) //Move Missile
        {
            if(!missiles[i].moveMissile( window.getSize() ))
            {
                missiles.erase(missiles.begin() + i);
                continue;
            }
            window.draw(missiles[i].sprite);
            for (size_t j = 0; j < enemies.size(); j++)
            {
                
                if(getDistance(missiles[i].sprite.getPosition(), enemies[j].sprite.getPosition()) < 50)
                {
                    missiles.erase(missiles.begin() + i);
                    enemies.erase(enemies.begin() + j);
                    break;
                }
            }
            
        }   
        window.draw(player.sprite);
        window.display();
    }
    
    return 0;
}