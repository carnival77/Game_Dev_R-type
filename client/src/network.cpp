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
    // _socket.open(udp::v4());
}


void Network::write(std::string data) {
    _socket.send_to(boost::asio::buffer(data), _remote_endpoint);
}


size_t Network::read() {
    // reads message from server
    // placing contents in reply buffer
    // and returning the number of bytes read
    udp::endpoint sender_endpoint;
    size_t reply_length = _socket.receive_from(
        boost::asio::buffer(reply, _max_length), sender_endpoint);
    return reply_length;
}


std::string Network::extract_payload(size_t reply_length) {
    // returns only the message part of the buffer, as a string object
    std::string data(reply);
    return data.substr(0, reply_length);
}
