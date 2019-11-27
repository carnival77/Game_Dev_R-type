#include <iostream>
#include <string>
#include "server.hpp"


Server::Server(std::string hostname, unsigned short port)
    : _socket(_io_context, udp::endpoint(udp::v4(), port)) 
    {
    start_receive();
    _io_context.run();
}


void Server::start_receive() {
    // reception handler, endpoint, handler callback
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        _remote_endpoint,
        boost::bind(&Server::handle_receive, 
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}


void Server::handle_receive(const boost::system::error_code& error,
                            std::size_t bytes_transferred) {
    // we can use instance variables in this handler because "this" was bound to it
    // write up to the length (else we read garbage)
    std::cout.write(_recv_buffer.data(), bytes_transferred); 
    if (error) {
    std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
    boost::shared_ptr<std::string> message(
        new std::string("hello from server\n"));

    _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
        boost::bind(&Server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    start_receive();
    }
}


void Server::handle_send(boost::shared_ptr<std::string> /*message*/,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/) {
}