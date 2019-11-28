#include <iostream>
#include "server.hpp"


<<<<<<< HEAD

class udp_server
{
public:
  udp_server(boost::asio::io_context& io_context)
    : socket_(io_context, udp::endpoint(udp::v4(), 244))
  {
    start_receive();
  }

private:
  void start_receive()
  {
    // std::string data = std::string("");
    // boost::asio::mutable_buffer buf = boost::asio::buffer(data);

    // size_t len = socket_.receive_from(
    //     boost::asio::buffer(buf), remote_endpoint_);

    socket_.async_receive_from(
        boost::asio::buffer(recv_buffer_), // reception buffer
        remote_endpoint_, // endpoint
        boost::bind(&udp_server::handle_receive, this,  // handler
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred)
    );
    // std::cout << buf.data() << "*\n";
  }

  void handle_receive(const boost::system::error_code& error,
      std::size_t bytes_transferred)
  {
    // we can use instance variables in this handler because "this" was bound to it
    std::cout.write(recv_buffer_.data(), bytes_transferred); // write up to the length (else we read garbage)
    if (error) {
      std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
      boost::shared_ptr<std::string> message(
          new std::string("hello from server\n"));

      socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
          boost::bind(&udp_server::handle_send, this, message,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

      start_receive();
    }
  }

  void handle_send(boost::shared_ptr<std::string> /*message*/,
      const boost::system::error_code& /*error*/,
      std::size_t /*bytes_transferred*/)
  {
  }

  udp::socket socket_;
  udp::endpoint remote_endpoint_;
  boost::array<char, 128> recv_buffer_;
};


int main()
{
=======
int main(int argc, char* argv[]) {
>>>>>>> 98caf0a4099d35e9b9a8ebb4170077bdd9a17e27
    std::cout << "I'm the server\n";
    try {
      if (argc != 3) {
        std::cerr << "Usage: server <host> <port>\n";
        return 84;
      }
      std::string hostname = argv[1];
      unsigned short port = std::stoi(argv[2]);

      Server server(hostname, port);
      std::cout << "Listening on port " << port << " host " << hostname << "\n";
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    return 0;
}