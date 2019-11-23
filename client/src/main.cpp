#include <iostream>
#include <SFML/Graphics.hpp>
#include "playerTextures.h"

int main()
{
    std::cout << "I'm the client\n";
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Client Window", sf::Style::Close);
    window.setVerticalSyncEnabled(false);
    
    auto playersShips = loadPlayerShip();
    
    int i = 0;
    float speed = 0.5;
    sf::Sprite player = playersShips[0];
    while (window.isOpen())
    {
        i++;
        i = i% 5;
        //player = playersShips[0];
        //std::cout << window.getPosition().x << "," << window.getPosition().y<< "\n";
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type == evnt.Closed)
                window.close();
        }
        window.clear();
        window.draw(player);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            player.move(sf::Vector2f(-speed,0.0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            player.move(sf::Vector2f(speed,0.0));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            player.move(sf::Vector2f(0.0,-speed));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            player.move(sf::Vector2f(0.0,speed));
        window.display();
    }
    
    return 0;
}