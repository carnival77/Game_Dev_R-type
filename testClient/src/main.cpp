#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
using namespace std;

using boost::asio::ip::udp;

int main()
{
    std::cout << "I'm the test client\n";

    boost::asio::io_context io_context;

    udp::resolver resolver(io_context);
    udp::endpoint receiver_endpoint =
    *resolver.resolve(udp::v4(), "localhost", "6676");

    udp::socket socket(io_context);
    socket.open(udp::v4());

    // FIXME: if client runs before server, client hangs

    boost::array<char, 1> send_buf  = { 0 };

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;

    for (int n=0;n<10;n++) {
        // send a datagram to an endpoint
        // datagram is a constant buffer sequence
        socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

        size_t len = socket.receive_from(
            boost::asio::buffer(recv_buf), sender_endpoint);
        std::cout.write(recv_buf.data(), len);
        // write data from server
    }
    return 0;
}