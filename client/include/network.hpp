#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::udp;


class Network {
    public:
        Network(std::string hostname, unsigned short port);
        void read();
        void write(std::string data);

    private:
        boost::asio::io_context _io_context;
        udp::socket _socket;
        boost::array<char, 128> _recv_buf;
        udp::endpoint _receiver_endpoint;
};