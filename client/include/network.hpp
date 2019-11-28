#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#define MAX_DATAGRAM_LENGTH 1024

using boost::asio::ip::udp;


class Network {
    public:
        Network(std::string hostname, unsigned short port);
        void write(std::string data);
        size_t read();
        char reply[MAX_DATAGRAM_LENGTH];
        std::string extract_payload(size_t reply_length);

    private:
        boost::asio::io_context _io_context;
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        int _max_length = MAX_DATAGRAM_LENGTH;
        boost::array<char, MAX_DATAGRAM_LENGTH> _recv_buf;
};