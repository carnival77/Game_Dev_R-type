#include "server.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "rtype_common/parsing.hpp"
#include "rtype_common/protocol.hpp"


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
            command_hello(message);
        } else if (rtype_common::starts_with(message, "KEY")){
            command_key(message);
        }
        start_receive();
    }
}


void Server::command_hello(std::string message) {
    async_send_only("OK");
}


void Server::command_key(std::string message) {
    std::vector<std::string> split_vect = rtype_common::split(message, ":");
    std::string key_value = split_vect[1];
    if (key_value == "LEFT") {
        command_key_left(message);
    } else if (key_value == "RIGHT") {
        command_key_right(message);
    } else if (key_value == "UP") {
        command_key_up(message);
    } else if (key_value == "DOWN") {
        command_key_down(message);
    }
}


void Server::command_key_left(std::string message) {
    _game_state.player.x = _game_state.player.x - PLAYER_SPEED;
    int player_idx = 0;
    std::string response = rtype_common::pack_player(player_idx, _game_state.player.x, _game_state.player.y, "LEFT");
    async_send_only(response);
}


void Server::command_key_right(std::string message) {
    _game_state.player.x = _game_state.player.x + PLAYER_SPEED;
    int player_idx = 0;
    std::string response = rtype_common::pack_player(player_idx, _game_state.player.x, _game_state.player.y, "RIGHT");
    async_send_only(response);
}


void Server::command_key_up(std::string message) {
    _game_state.player.y = _game_state.player.y - PLAYER_SPEED;
    int player_idx = 0;
    std::string response = rtype_common::pack_player(player_idx, _game_state.player.x, _game_state.player.y, "UP");
    async_send_only(response);
}


void Server::command_key_down(std::string message) {
    _game_state.player.y = _game_state.player.y + PLAYER_SPEED;
    int player_idx = 0;
    std::string response = rtype_common::pack_player(player_idx, _game_state.player.x, _game_state.player.y, "DOWN");
    async_send_only(response);
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