#include <iostream>
#include <string>
#include "server.h"
using namespace std;

Server::Server(string hostname, unsigned short port)
    : socket(_io_context, udp::endpoint(udp::v4(), port)) 
    {
        cout<<"this is server.cpp and port is "<<port<<endl;
    cout<<"servet test1"<<endl;
    start_receive();
    _io_context.run();
}

void Server::start_receive() {
    // reception handler, endpoint, handler callback
    socket.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        client_endpoint,
        boost::bind(&Server::handle_receive, 
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
    cout<<"servet test2"<<endl;

    //
    size_t len = socket.receive_from(
        boost::asio::buffer(_recv_buffer), client_endpoint);

    cout<<"servet test3 : "<<len << endl;
        std::cout << "Reply from client is: ";
    std::cout.write(_recv_buffer.data(), len);
    //

}

void Server::handle_receive(const boost::system::error_code& error,
                            std::size_t bytes_transferred) {
    // we can use instance variables in this handler because "this" was bound to it
    // write up to the length (else we read garbage)

    if (error) {
        std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
        //new_session.reset(new session(socket, client_endpoint, room_));
        new_session.reset(new session(socket, client_endpoint, room_));
		new_session->start();
        


        boost::shared_ptr<std::string> message(
            new std::string("This is server. to client\n"));
            // from server to client


cout<<"servet test4"<<endl;

        socket.async_send_to(boost::asio::buffer(*message), client_endpoint,
            boost::bind(&Server::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

cout<<"servet test5"<<endl;

        start_receive();

        cout<<"servet test6"<<endl;

    }
}


void Server::handle_send(boost::shared_ptr<std::string> message,
    const boost::system::error_code& error,
    std::size_t bytes_transferred) {
        if (!error) {
	}
	else {
		std::cout << error.message() << std::endl;
	}
}