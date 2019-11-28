#include "Menu.h"

Menu::Menu(AppDataRef data) : data(data)
{
    if (!font.loadFromFile("./fonts/Big Space.otf"))
    {
        return;
    }
    data->textures.load("Menu background", "./textures/menuBackground.jpg");
    background.setTexture(data->textures.get("Menu background"));
    selectedItemIndex = 0;
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Magenta);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(sWidth / 2, sHeight / (ITEMS + 1) * 1));
    menu[0].setScale(3,3);

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Exit");
    menu[1].setPosition(sf::Vector2f(sWidth / 2, sHeight / (ITEMS + 1) * 2));
    menu[1].setScale(3,3);

}

Menu::~Menu()
{

}

void Menu::run()
{
    processEvents();
    update();
    render();
}

void Menu::processEvents()
{
    sf::Event event;
    while (data->window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            data->window.close();
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
                    data->manager.changeScreen(ScreenState(new Game(data)));
                    break;
                case 1: 
                    data->window.close();
                    break;
                }
            }
        }
    }
}

void Menu::update()
{

}

void Menu::render()
{
    data->window.clear();
    data->window.draw(background);
    for (int i = 0; i < ITEMS; i++)
    {
        data->window.draw(menu[i]);
    }
    data->window.display();
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