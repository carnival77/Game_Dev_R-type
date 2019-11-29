#include <iostream>
#include "network.hpp"


Network::Network(std::string hostname, unsigned short port) 
: _socket(_io_context, udp::endpoint(udp::v4(), port+1))
  // FIXME: what does the endpoint represent here? Why we need a different port number from the server?
{
    // address type, hostname, service type (which port to bind to)
    // we can either leave service empty and set port manually, or pass the port as a string
    udp::resolver resolver(_io_context);
    udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), hostname, std::to_string(port));
    _remote_endpoint = *endpoints.begin();
}


void Network::write(const char data[], size_t length) {
    /**
     * Send data to the server.
    **/
    _socket.send_to(boost::asio::buffer(data, length), _remote_endpoint);
    std::cout << "[NETWORK LOG] Wrote: " << data << "\n";
}


// void Network::write(GameInfo data) {
//     /**
//      * Send data to the server.
//     **/
//     GameInfo pod_array[] = { data };
//     _socket.send_to(boost::asio::buffer(pod_array, max_length), _remote_endpoint);
//     // std::cout << "[NETWORK LOG] Wrote: " << data << "\n";
// }


size_t Network::read() {
    /** 
     * Read message from server, placing result in reply buffer.
     * Returns number of bytes read.
    **/
    size_t reply_length = _socket.receive_from(
        boost::asio::buffer(reply, max_length), _remote_endpoint);
	std::cout << "[NETWORK LOG] Got: " << extract_payload(reply_length) << " ( " << reply_length << " bytes )\n";
    return reply_length;
}


std::string Network::extract_payload(size_t reply_length) {
    /**
     * Extract the message part of the buffer.
    **/
    std::string data(reply);
    return data.substr(0, reply_length);
}
