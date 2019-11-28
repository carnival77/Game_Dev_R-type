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


void Network::read() {

}


void Network::write(std::string data) {
    _socket.send_to(boost::asio::buffer(data), _remote_endpoint);
}