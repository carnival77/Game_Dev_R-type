#include "server.h"
using namespace std;

int main(int argc, char* argv[]) 
{
    std::cout << "I'm the server\n";

    short port = 6690;
    std::string hostname="localhost";
    Server server(hostname, port);

    return 0;
}