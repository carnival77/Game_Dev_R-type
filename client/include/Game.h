#pragma once
#include "SFML/Graphics.hpp"
#include "player.h"
#include "enemy.h"
#include "missile.h"
#include "background.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "cScreen.h"
using boost::asio::ip::udp;
#include "cTexture.h"
#include "network.hpp"
#include <thread>
using namespace std;

class Game : public cScreen
{
public:
    Game(boost::asio::io_context& io_context,std::string hostname, unsigned short port);
    
    // Network
    boost::asio::ip::udp::endpoint client_endpoint; 
    boost::asio::ip::udp::endpoint server_endpoint; 
    boost::array<char, 256> recv_buffer_;
    boost::asio::ip::udp::socket socket;
    boost::asio::io_context io_context;
    std::string hostname;
    unsigned short port;
    int Main_loop(sf::RenderWindow &window, vector<cScreen*> Screens);

    void start_receive();
    //
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
    void sendToServer(string msg);

    void handle_receive(const boost::system::error_code& error,
        std::size_t /*bytes_transferred*/);

    void handle_send(boost::shared_ptr<std::string> /*message*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/);

    void Init(boost::asio::io_context& io_context,std::string hostname, unsigned short port);
    
    void handle_write(const boost::system::error_code& e);

    void do_write(Game msg);
};