
#include <iostream>
#include "screens.h"


int main(int argc, char** argv)
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator

    std::vector<cScreen*> Screens;
	int state = 1;

	//Window creation
	sf::RenderWindow app(sf::VideoMode::getDesktopMode(), "Client Rtype", sf::Style::Close);

    app.setFramerateLimit(60);

	//App.setMouseCursorVisible(false);

	//Screens preparations
    float height = app.getSize().y;
    float width = app.getSize().x;
	Game game;
	Screens.push_back(&game);
	Menu menu(width, height);
	Screens.push_back(&menu);

	cout<<"test1"<<endl;

	// // Boost
    //      boost::asio::io_service io_service;
	// 	 cout<<"test2"<<endl;

    // udp::socket socket(io_service);
    // socket.open(udp::v4());

    // udp::resolver resolver(io_service);
    // udp::resolver::query query(udp::v4(),socket.remote_endpoint().address(),"daytime");
    // udp::endpoint receiver_endpoint = *resolver.resolve(query);

	

    //     // FIXME: if client runs before server, client hangs
    //     // boost::array<char, 128> send_buf  = {{ 1, 2, 4, 52, 43 }};
    //     std::string send_buf = std::string("hello from client\n");
    //     std::cout << "Sending to server: " << send_buf << "\n";

    //     // send a datagram to an endpoint
    //     // datagram is a constant buffer sequence
    //     socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    //     boost::array<char, 128> recv_buf;
    //     udp::endpoint sender_endpoint;
    //     size_t len = socket.receive_from(
    //         boost::asio::buffer(recv_buf), sender_endpoint);

    //     std::cout.write(recv_buf.data(), len);
	// cout<<"test"<<endl;
	//Main loop
	while (state >= 0)
	{
		state = Screens[state]->run(app);
		// std::cout << "Peer IP: " << socket.remote_endpoint().address().to_string() << std::endl;
    
	}
    app.close();
    return 0;
}