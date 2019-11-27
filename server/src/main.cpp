#include <iostream>
#include "server.hpp"


int main(int argc, char* argv[]) {
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