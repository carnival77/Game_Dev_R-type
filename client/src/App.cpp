#include "App.h"
#include "Splash.h"

App::App(int width, int height, std::string title)
{
    data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
    data->manager.changeScreen(ScreenState(new Splash(data)));
    data->window.setFramerateLimit(60);
    this->init();
}

void App::init()
{
    while (data->window.isOpen())
    {
        data->manager.updateManager();
        data->manager.getCurrent()->run();
    }
    
}