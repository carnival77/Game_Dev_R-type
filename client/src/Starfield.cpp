#include "Starfield.h"

Starfield::Starfield(AppDataRef data)
{
    this->data = data;
    sf::Sprite dummy1, dummy2;

    dummy1.setTexture(data->textures.get("GameBackground"));
    dummy2.setTexture(data->textures.get("GameBackground"));

    dummy1.setPosition(0, 0);
    dummy2.setPosition(dummy2.getGlobalBounds().width, 0);

    sprites.push_back(dummy1);
    sprites.push_back(dummy2);
}

void Starfield::update()
{
    for (size_t i = 0; i < sprites.size(); i++)
    {
        sf::Vector2f position = sprites[i].getPosition();
        sprites[i].move(-STARFIELD_SPEED, 0.0f);

        if (sprites[i].getPosition().x < 0 - sprites[i].getLocalBounds().width)
        {
            sf::Vector2f position(data->window.getSize().x, sprites[i].getPosition().y);

            sprites[i].setPosition(position);
        }
    }
}

void Starfield::draw()
{
    for (size_t i = 0; i < sprites.size(); i++)
    {
        data->window.draw(sprites[i]);
    }
    
}