#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include "server.hpp"


#define PLAYER_SPEED 4.0f


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
    std::cout << "[MESSAGE LOG] Received: " << extract_payload(bytes_transferred) 
              << " (" << bytes_transferred << " bytes) " << "\n";

    if (error) {
        std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
        std::string message = extract_payload(bytes_transferred);
        if (message == "HELLO") {
            boost::shared_ptr<std::string> response(new std::string("OK"));

            _socket.async_send_to(boost::asio::buffer(*response), _remote_endpoint,
                boost::bind(&Server::handle_send, this, response,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
            std::cout << "[MESSAGE LOG] Sent: " << *response << "\n";
        } else if (boost::starts_with(message, "KEY")){
            std::vector<std::string> split_vect;
            boost::split(split_vect, message, boost::is_any_of(":"));
            for (auto e = split_vect.begin(); e != split_vect.end(); e++) {
                std::cout << *e << " ";
            }
            std::cout << "\n";
            std::string key_value = split_vect[1];
            if (key_value == "LEFT") {
                _game_state.player.x = _game_state.player.x - PLAYER_SPEED;
                boost::shared_ptr<std::string> response(
                    new std::string("PLAYER:" + std::to_string(_game_state.player.x)
                                    + ";" + std::to_string(_game_state.player.y)));
                _socket.async_send_to(boost::asio::buffer(*response), _remote_endpoint,
                boost::bind(&Server::handle_send, this, response,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
                std::cout << "[MESSAGE LOG] Sent: " << *response << "\n";
            }
        }

        start_receive();
    }
}


void Server::handle_send(boost::shared_ptr<std::string> /*message*/,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/) {
}


std::string Server::extract_payload(size_t bytes_transferred) {
    std::string data(_recv_buffer.data());
    return data.substr(0, bytes_transferred);
}