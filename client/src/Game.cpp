#include "Game.h"
#include "screens.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/basic_datagram_socket.hpp>
using namespace std;
using boost::asio::ip::udp;

Game::Game(boost::asio::io_context& io_context,std::string hostname, unsigned short port)
: socket(io_context)
{
    loadTextures();
    player.setAnimation(textures, 1);
    background.setTexture(textures.get(Textures::GameBackground));

    // Network
    int max_length = 1024;

    udp::resolver resolver(io_context);
    udp::endpoint server_endpoint =
    *resolver.resolve(udp::v4(), hostname, std::to_string(port));

    socket.open(udp::v4());

cout<<"Test1"<<endl;
    // boost::array<char, 1> send_buf  = { 0 };
    // socket.send_to(boost::asio::buffer(send_buf), server_endpoint);

    //string testmsg = "This is client. to server\n";

    //sendToServer(testmsg);

    //

    boost::shared_ptr<std::string> message(
            new std::string("This is client. to server\n"));
    //         // from server to client

            

    cout<<"Test2"<<endl;

   // boost::array<char, 128> message2  = {d};

    //sendToServer(message);
    // sendToServer(message);
    socket.async_send_to(boost::asio::buffer(recv_buffer_), server_endpoint,
        boost::bind(&Game::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
            
cout<<"Test3"<<endl;
    start_receive();
    cout<<"Test4"<<endl;

}

void Game::loadTextures()
{
    textures.load(Textures::Players, "./textures/players.gif");
    textures.load(Textures::PlayerMissile, "./textures/playerMissiles.gif");
    textures.load(Textures::RedPlane, "./textures/redEnemyShip.gif");
    textures.load(Textures::GameBackground, "./textures/background.jpg");
}

///-----------------------------------------------------------//
int Game::run(sf::RenderWindow &window)
{
    int state = processEvents(window);
    int state2 = update(window); // 0  = keep processing.
    render(window);
    if(state != 0)
        return state;
    else 
        return state2;
}
///-----------------------------------------------------------//

int Game::processEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            return -1;
            //cout<<"exit1"<<endl;
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Escape:
                //cout<<"play"<<endl;
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
    ///-----------------------------------------------------------//
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
    ///-----------------------------------------------------------//
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

void Game::start_receive()
{
    //initialize the rmoete_endpoint_
    //boost::asio::ip::udp::endpoint sender_endpoint;
    socket.async_receive_from(
        //boost::asio::buffer(recv_buffer_), client_endpoint,
        boost::asio::buffer(recv_buffer_), server_endpoint,
        boost::bind(&Game::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    cout<<"Test5"<<endl;
    size_t len = socket.receive_from(
        //boost::asio::buffer(recv_buffer_), client_endpoint); // succed rate : 50%
         boost::asio::buffer(recv_buffer_), server_endpoint); // same
    cout<<"Test6"<<endl;
    std::cout << "Reply from server is: ";
    std::cout.write(recv_buffer_.data(), len);
    cout<<"Test7"<<endl;
}

void Game::handle_receive(const boost::system::error_code& error,
    std::size_t bytes_transferred)
{

    if (!error || error == boost::asio::error::message_size)
    {
        // std::string receive_json = std::string(recv_buffer_.begin(),
        //     recv_buffer_.begin() + bytes_transferred);
        

        // else if (type == "newplayer") {
        //     sf::Vector2f initialpos{ x,y };
        //     std::cout << "player id" + playerid << std::endl;
        //     enemies.push_back(std::make_unique<EnemyPlayer>(m_game, playerid, initialpos));
        // }

        start_receive();
    }
    // else {
    //     std::cout << error.message() << std::endl;
    // }
}

void Game::handle_send(boost::shared_ptr<std::string> message,
    const boost::system::error_code& error,
    std::size_t bytes_transferre)
{
}

// void Game::sendToServer(string msg) {
//     boost::shared_ptr<std::string> message(
//             new std::string(msg));
//             // from server to client

//     socket.async_send_to(boost::asio::buffer(recv_buffer_), server_endpoint,
//         boost::bind(&Game::handle_send, this, message,
//             boost::asio::placeholders::error,
//             boost::asio::placeholders::bytes_transferred));
// }