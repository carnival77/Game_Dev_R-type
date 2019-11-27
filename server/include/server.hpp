#pragma once
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


class Server {
    public:
        Server(std::string hostname, unsigned short port);

    private:
        void start_receive();

        void handle_receive(const boost::system::error_code& error,
                            std::size_t bytes_transferred);

        void handle_send(boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);

        boost::asio::io_context _io_context;
        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        boost::array<char, 128> _recv_buffer;
};
