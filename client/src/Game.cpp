#include "Game.h"
#include <iostream>
#include <string>


Game::Game(AppDataRef data,std::string hostname, unsigned short port)
: network(hostname, port)
{
    this->data = data;
    loadTextures();

    //
	// establish connection with server
    //
	network.write("HELLO");
    if (network.extract_payload(network.read()) != "OK") {
        std::cerr << "Could not connect to server.\n";
    } else {
        std::cout << "Connected to server.\n";
    }

    player.network = &network;

    // std::string serial_str;
    // boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    // boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    // boost::archive::binary_oarchive oa(s);
    // oa << player.gameinfo;
    // s.flush();
    // int len = serial_str.length();
    // char gameinfo_payload[len+1];
    // std::strcpy(gameinfo_payload, serial_str.c_str());

    // std::stringstream ss;
    // boost::archive::binary_oarchive oa(ss);
    // oa << player.gameinfo;
    // const char* gameinfo_payload = ss.str().data();
    // network.write(gameinfo_payload, ss.str().size());

    loadTextures();
    player.setAnimation(data->textures, 1);
    background.setTexture(data->textures.get("GameBackground"));
}

void Game::loadTextures()
{
    data->textures.load("Players", "./textures/players.gif");
    data->textures.load("PlayerMissile", "./textures/playerMissiles.gif");
    data->textures.load("RedPlane", "./textures/redEnemyShip.gif");
    data->textures.load("GameBackground", "./textures/background.jpg");
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
    static int generator = 0;
    static const int power = 40; 
    generator++;
    if(generator > power)//New Enemy
    {
        generator = 0;
        Enemy enemy(sWidth, (rand() % (sHeight - 300) +100));
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
    float speed = 7;
    if(player.movePlayer(speed))
    {
        Missile dummy(player.sprite.getPosition().x + 50 , player.sprite.getPosition().y + 40);
        missiles.push_back(dummy);
    }
    //Update missiles and check collisions
    for (size_t i = 0; i < missiles.size(); i++) //Move Missile
    {
        if(!missiles[i].moveMissile(data->window.getSize()))
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
            data->window.close();
            //TODO: add game over screen
        }
    }
}

void Game::render()
{
    data->window.clear();

    data->window.draw(background);
    
    //draw()
    //Draw enemies
    for (size_t i = 0; i < enemies.size(); i++) 
    {
        data->window.draw(enemies[i].sprite);
    }
    //Draw missiles
    for (size_t i = 0; i < missiles.size(); i++)
    { 
        data->window.draw(missiles[i].sprite);
    }
    //Draw player
    data->window.draw(player.sprite);
    // sf::FloatRect dummy = player.sprite.getGlobalBounds();
    // sf::RectangleShape dummy2(sf::Vector2f(dummy.width, dummy.height));
    // dummy2.setOutlineThickness(2);
    // dummy2.setOutlineColor(sf::Color::Red);
    // dummy2.setFillColor(sf::Color(0,0,0,0));
    // dummy2.setPosition(player.sprite.getPosition());
    // data->window.draw(dummy2);
    data->window.display();
}
