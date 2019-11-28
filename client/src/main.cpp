#include <iostream>
#include "screens.h"


int main(int argc, char** argv)
{
    std::cout << "I'm the client\n";
    srand(time(NULL));  // initialise seed for random number generator

    std::vector<cScreen*> Screens;
	int state = 1;

	//Window creation
	sf::RenderWindow app(sf::VideoMode::getDesktopMode(), "Client Rtype", sf::Style::Close);

    app.setFramerateLimit(60);

	//App.setMouseCursorVisible(false);

	//Screens preparations
    float height = app.getSize().y;
    float width = app.getSize().x;
	Game game("127.0.0.1", 13);
	Screens.push_back(&game);
	Menu menu(width, height);
	Screens.push_back(&menu);

	//Main loop
	while (state >= 0)
	{
		state = Screens[state]->run(app);
	}
    app.close();
    return 0;
}