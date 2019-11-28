#pragma once
#include <SFML/Graphics.hpp>
#include "Screens.h"
#include "App.h"

#define ITEMS 2

class Menu : public cScreen
{
public:
    Menu(AppDataRef data);
    ~Menu();
    virtual void run();
private:
    void processEvents();
    void update();
    void render();

    sf::Font font;
    sf::Text menu[ITEMS];
    int selectedItemIndex;
    AppDataRef data;
    sf::Sprite background;

    void moveUp();
    void moveDown();
};