#pragma once
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#define MAX_DATAGRAM_LENGTH 1024

using boost::asio::ip::udp;


class Network {
    public:
        Network(std::string hostname, unsigned short port);
        void write(std::string);
        size_t read();
        std::string extract_payload(size_t reply_length);
        std::string read_payload();

        char reply[MAX_DATAGRAM_LENGTH];
        int max_length = MAX_DATAGRAM_LENGTH;
    private:
        boost::asio::io_context _io_context;
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
};