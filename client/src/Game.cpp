#include "Game.h"
#include <iostream>
#include <string>


#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::udp;


Game::Game(std::string hostname, unsigned short port)
// : network(hostname, port)
{
    loadTextures();
    player.setAnimation(textures, 1);
    background.setTexture(textures.get(Textures::GameBackground));

    //
	// establish connection with server
    //
	// network.write(std::string("HELLO\n"));
    int max_length = 1024;

    boost::asio::io_context io_context;

    // FIXME: what does the endpoint represent here? Why we need a different port number from the server?
    udp::socket socket(io_context, udp::endpoint(udp::v4(), port+1));

    udp::resolver resolver(io_context);
    // address type, hostname, service type (which port to bind to)
    // we can either leave service empty and set port manually, or pass the port as a string
    udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), hostname, std::to_string(port));
    udp::endpoint remote_endpoint = *endpoints.begin();

    std::cout << "Enter message: ";
    char request[max_length];
    std::cin.getline(request, max_length);
    size_t request_length = std::strlen(request);
    socket.send_to(boost::asio::buffer(request, request_length), remote_endpoint);
    // std::string payload;
    // std::cin >> payload;
    // socket.send_to(boost::asio::buffer(payload), remote_endpoint);

    char reply[max_length];
    udp::endpoint sender_endpoint;
    size_t reply_length = socket.receive_from(
        boost::asio::buffer(reply, max_length), sender_endpoint);
    std::cout << "Reply is: ";
    std::cout.write(reply, reply_length);
    std::cout << "\n";    //
    //

	// std::cout << network.read();
}

void Game::loadTextures()
{
    textures.load(Textures::Players, "./textures/players.gif");
    textures.load(Textures::PlayerMissile, "./textures/playerMissiles.gif");
    textures.load(Textures::RedPlane, "./textures/redEnemyShip.gif");
    textures.load(Textures::GameBackground, "./textures/background.jpg");
}


int Game::run(sf::RenderWindow &window)
{
    int state = processEvents(window);
    int state2 = update(window);
    render(window);
    if(state != 0)
        return state;
    else 
        return state2;
}

int Game::processEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            return -1;
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                    return 1;
                    break;
            }
        }
    }
    return 0;
}

int Game::update(sf::RenderWindow &window)
{
    static int generator = 0;
    static const int power = 40; 
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
    static const float speed = 7;
    if(player.movePlayer(speed))
    {
        Missile dummy(player.sprite.getPosition().x + 50 , player.sprite.getPosition().y + 40);
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
            return -1;
        }
    }
    return 0;
}

void Game::render(sf::RenderWindow &window)
{
    window.clear();

    window.draw(background);
    
    //draw()
    //Draw enemies
    for (size_t i = 0; i < enemies.size(); i++) 
    {
        window.draw(enemies[i].sprite);
    }
    //Draw missiles
    for (size_t i = 0; i < missiles.size(); i++)
    { 
        window.draw(missiles[i].sprite);
    }
    //Draw player
    window.draw(player.sprite);
    // sf::FloatRect dummy = player.sprite.getGlobalBounds();
    // sf::RectangleShape dummy2(sf::Vector2f(dummy.width, dummy.height));
    // dummy2.setOutlineThickness(2);
    // dummy2.setOutlineColor(sf::Color::Red);
    // dummy2.setFillColor(sf::Color(0,0,0,0));
    // dummy2.setPosition(player.sprite.getPosition());
    // window.draw(dummy2);
    window.display();
}