#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


class udp_server
{
public:
  udp_server(boost::asio::io_context& io_context)
    : socket_(io_context, udp::endpoint(udp::v4(), 13))
  {
    start_receive();
  }

private:
  void start_receive()
  {
    std::string data = std::string("");
    // boost::asio::mutable_buffer buf = boost::asio::buffer(data);
    boost::array<char, 128> buf;

    size_t len = socket_.receive_from(
        boost::asio::buffer(buf), remote_endpoint_);
    std::cout.write(buf.data(), len); // write up to the length (else we read garbage)

    socket_.async_receive_from(
        buf, // reception buffer
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
    std::cout << recv_buffer_.data() << "*\n";
    if (error) {
      std::cerr << "( " << error << " )" << error.message() << std::endl;
    } else {
      boost::shared_ptr<std::string> message(
          new std::string("hello there\n"));

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
  boost::asio::mutable_buffer recv_buffer_;
};


int main()
{
    std::cout << "I'm the server\n";
    try {
      boost::asio::io_context io_context;
      udp_server server(io_context);
      io_context.run();
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    return 0;
}