#pragma once
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/make_shared.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include <exception>
#include "room.h"
#include "participant.h"
#include "session.h"

using boost::asio::ip::udp;


class Server {
    public:
        Server(std::string hostname, unsigned short port);
        udp::endpoint client_endpoint; // = sender endpoint 
        udp::endpoint server_endpoint; // = receiver endpoint 

    private:
        void start_receive();

        void handle_receive(const boost::system::error_code& error,
                            std::size_t bytes_transferred);

        void handle_send(boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);

        boost::asio::io_context _io_context;
        //boost::shared_ptr<boost::asio::ip::udp::socket> socket;
        udp::socket socket;

        boost::array<char, 256> _recv_buffer;

        	//The next connection to be accepted
	    boost::shared_ptr<session> new_session;

	    room room_;
};
