#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using std::string;
using boost::asio::ip::udp;


class Server {
  /* a UDP server for R-Type */

  public:
    Server(boost::asio::io_context& io_context, string hostname, unsigned short port)
      : socket_(io_context, udp::endpoint(boost::asio::ip::make_address(hostname), port))
      /* initialise a socket object with the given context
         and receiver */
      // TODO: DNS resolution of non-IP address hostnames
    {
      start_receive();  // start listening for client connections
    }

  private:
    void start_receive() {
      std::cout << "Listening for clients\n";
      socket_.async_receive_from(
          boost::asio::buffer(recv_buffer_), remote_endpoint_,
          boost::bind(&Server::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,
        std::size_t /*bytes_transferred*/)
    {
      if (!error)
      {
        std::cout << "received message\n";
        std::cout << boost::asio::placeholders::bytes_transferred;

        boost::shared_ptr<std::string> message(
            new std::string("message from server"));

        socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
            boost::bind(&Server::handle_send, this, message,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));

        start_receive();
      }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/)
    {
        std::cout << "sending messages\n";
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 1> recv_buffer_;
};


int main()
{
    std::cout << "I'm the server\n";
    
    int port = 6666;
    std::string hostname = "127.0.0.1";

    try {
        boost::asio::io_context io_context;
        Server server(io_context, hostname, port);
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}