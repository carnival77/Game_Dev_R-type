#pragma once
#include <SFML/Graphics.hpp>
#include "cScreen.h"
#include "constants.h"

#define ITEMS 2

class Menu : public cScreen
{
public:
    Menu();
    ~Menu();
    virtual int run(sf::RenderWindow &window);
private:
    int processEvents(sf::RenderWindow &window);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);

    sf::Font font;
    sf::Text menu[ITEMS];
    int selectedItemIndex;

    void moveUp();
    void moveDown();
};