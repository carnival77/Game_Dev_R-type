#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


int main(int argc, char** argv)
{
    std::cout << "I'm the test client\n";
    try {
        if (argc != 2)
        {
        std::cerr << "Usage: client <host>" << std::endl;
        return 1;
        }

        boost::asio::io_context io_context;

        udp::resolver resolver(io_context);
        udp::endpoint receiver_endpoint =
        *resolver.resolve(argv[1], "daytime").begin();

        udp::socket socket(io_context);
        socket.open(udp::v4());

        // FIXME: if client runs before server, client hangs
        // boost::array<char, 128> send_buf  = {{ 1, 2, 4, 52, 43 }};
        std::string send_buf = std::string("hello from client\n");


        boost::array<char, 128> recv_buf;
        udp::endpoint sender_endpoint;

        for (;;) {
            // send a datagram to an endpoint
            // datagram is a constant buffer sequence
            socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

            size_t len = socket.receive_from(
                boost::asio::buffer(recv_buf), sender_endpoint);
            std::cout.write(recv_buf.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}