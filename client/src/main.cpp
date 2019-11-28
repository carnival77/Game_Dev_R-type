#include <iostream>
#include "App.h"
#include "constants.h"


int main(int argc, char** argv)
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator

	App app(sWidth, sHeight, "Rtype Client");
    return 0;
}