#include "server.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "rtype_common/parsing.hpp"


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
    std::cout << "[NETWORK LOG] Queued async receive.\n";
}


void Server::handle_receive(const boost::system::error_code& error,
                            std::size_t bytes_transferred) {
    // we can use instance variables in this handler because "this" was bound to it
    // write up to the length (else we read garbage)
    std::cout << "[NETWORK LOG] Received: " << extract_payload(bytes_transferred) 
              << " (" << bytes_transferred << " bytes) " << "\n";

    if (error) {
        std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
        std::string message = extract_payload(bytes_transferred);
        if (message == "HELLO") {
            async_send_only("OK");
        } else if (rtype_common::starts_with(message, "KEY")){
            std::vector<std::string> split_vect = rtype_common::split(message, ":");
            std::string key_value = split_vect[1];
            if (key_value == "LEFT") {
                _game_state.player.x = _game_state.player.x - PLAYER_SPEED;
                std::string response = "PLAYER:" + std::to_string(_game_state.player.x) + 
                                       ";" + std::to_string(_game_state.player.y);
                async_send_only(response);
            }
        }

        start_receive();
    }
}


void Server::async_send_only(std::string message) {
    /**
     * Asynchronous (non-blocking) send with an empty callback. 
     **/
    _socket.async_send_to(boost::asio::buffer(message), 
                          _remote_endpoint,
                          boost::bind(&Server::handle_send_empty, 
                                      this, 
                                      message,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred
                          ));
    std::cout << "[NETWORK LOG] Queued async send for: " << message << "\n";
}


void Server::handle_send_empty(
    // boost::shared_ptr<std::string> /*message*/,
    std::string message,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/) {
    std::cout << "[NETWORK LOG] Sent: " << message << "\n";
}


std::string Server::extract_payload(size_t bytes_transferred) {
    std::string data(_recv_buffer.data());
    return data.substr(0, bytes_transferred);
}