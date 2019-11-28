#include "network.hpp"


Network::Network(std::string hostname, unsigned short port) 
: _socket(_io_context) 
{
    udp::resolver resolver(_io_context);
    udp::endpoint _receiver_endpoint = *resolver.resolve(hostname, "daytime").begin();
    _socket.open(udp::v4());
}


void Network::read() {

}


void Network::write(std::string data) {
    std::string buff = std::string("hello from client\n");
    _socket.send_to(boost::asio::buffer(buff), _receiver_endpoint);
}