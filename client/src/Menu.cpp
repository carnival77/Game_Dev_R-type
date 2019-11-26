#include "Menu.h"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("./fonts/arial.ttf"))
    {
        return;
    }
    selectedItemIndex = 0;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Magenta);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width / 2, height / (ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(width / 2, height / (ITEMS + 1) * 2));
}

Menu::~Menu()
{

}

int Menu::run(sf::RenderWindow &window)
{
    int state = processEvents(window);
    update(window);
    render(window);
    return state;
}

int Menu::processEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            return -1;
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                moveUp();
                break;
            case sf::Keyboard::Down:
                moveDown();
                break;
            case sf::Keyboard::Return:
                switch (selectedItemIndex)
                {
                case 0:
                    return 0;
                    break;
                case 1: 
                    return -1;
                    break;
                }
            }
        }
    }
    return 1;
}

void Menu::update(sf::RenderWindow &window)
{

}

void Menu::render(sf::RenderWindow &window)
{
    window.clear();
    for (int i = 0; i < ITEMS; i++)
    {
        window.draw(menu[i]);
    }
    window.display();
}

void Menu::moveUp()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex--;
    selectedItemIndex %= ITEMS;
    menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
}

void Menu::moveDown()
{
    menu[selectedItemIndex].setFillColor(sf::Color::White);
    selectedItemIndex++;
    selectedItemIndex %= ITEMS;
    menu[selectedItemIndex].setFillColor(sf::Color::Magenta);
}