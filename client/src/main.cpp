#include <iostream>
#include <SFML/Network.hpp>
#include "Game.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;


// float getDistance(sf::Vector2f fst, sf::Vector2f snd)
// {
//     const float x_diff = fst.x - snd.x;
//     const float y_diff = fst.y - snd.y;
//     return std::sqrt(x_diff * x_diff + y_diff * y_diff);
// }


unsigned short port = 6667;
sf::IpAddress ip = "localhost";
unsigned short serverPort = 6666;
sf::IpAddress serverIp = "localhost";


int main()
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator

    std::cout << "Sending message to the server\n";
    try {
        boost::asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint =
        *resolver.resolve(udp::v4(), argv[1], "daytime").begin();

        udp::socket socket(io_context);
        socket.open(udp::v4());

        boost::array<char, 1> send_buf  = {{ 0 }};
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

        boost::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;
        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);

        std::cout.write(recv_buf.data(), len);
    }
    // sf::UdpSocket socket;

    // Game game;
    // game.run();

    // prepare data to send
    sf::Packet packet;
    string data = "message from client";
    packet << data;

    // send data
    for (int i = 0; i < 1000; i++) {
    if (socket.send(packet, serverIp, serverPort) != sf::Socket::Done)
    {
        std::cerr << "Error sending data\n";
        // error...
    }
    }

    std::cout << "Receiving a message from the server\n";
    // bind the socket (prepare to listen)
    if (socket.bind(port, ip) != sf::Socket::Done) {
        std::cerr << "Error binding to socket\n";
        // error...
    }

    // receive data
    if (socket.receive(packet, ip, port) != sf::Socket::Done) {
        std::cerr << "Error receiving data\n";
    } else {
        std:cout << "Received data\n";
    }

    if (packet >> data) {
        std::cout << "Received: " << data << "\n";
    } else {
        std::cerr << "Error reading received data from packet\n";
    }

    // Game game;
    // game.run();
    return 0;
}