#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    std::cout << "I'm the client\n";
    sf::RenderWindow window(sf::VideoMode(512,512), "Client Window", sf::Style::Close | sf::Style::Default);

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if(evnt.type == evnt.Closed)
                window.close();
        }
        
    }
    
    return 0;
}