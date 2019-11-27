#include <iostream>
#include "screens.h"
#include "constants.h"


int main(int argc, char** argv)
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator

    std::vector<cScreen*> Screens;
	int state = 1;

	//Window creation
	sf::RenderWindow app(sf::VideoMode(sWidth, sHeight), "Client Rtype", sf::Style::Close);

    app.setFramerateLimit(60);

	//App.setMouseCursorVisible(false);

	//Screens preparations
	Game game;
	Screens.push_back(&game);
	Menu menu;
	Screens.push_back(&menu);

	//Main loop
	while (state >= 0)
	{
		state = Screens[state]->run(app);
	}
    app.close();
    return 0;
}