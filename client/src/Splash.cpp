#include "Splash.h"

Splash::Splash(AppDataRef data): data(data)
{
    loadTextures();
    background.setTexture(data->textures.get("Splash background"));
}

void Splash::run()
{
    processEvents();
    update();
    render();
}

void Splash::processEvents()
{
    sf::Event event;
    while (data->window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            data->window.close();
            break;
        }
    }
}

void Splash::update()
{
    if (clock.getElapsedTime().asSeconds() > SPLASH_TIME)
	{
        data->manager.changeScreen(ScreenState(new Menu(data)));
    }
}

void Splash::render()
{
    data->window.clear();
    data->window.draw(background);
    data->window.display();
}

void Splash::loadTextures()
{
    data->textures.load("Splash background", "./textures/splashBackground.jpg");
}
