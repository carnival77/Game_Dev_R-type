#include "playerTextures.h"

vector<sf::Sprite> loadPlayerShip()
{
    sf::Texture * playerTexture = new sf::Texture;
    playerTexture->loadFromFile("./textures/r-typesheet42.gif");
    //playerTexture->setSmooth(true);
    sf::Vector2u shapeSize = playerTexture->getSize();
    shapeSize.x /= 5;
    shapeSize.y /= 5;
    
    vector<sf::Sprite> result;
    sf::Sprite sprite;
    sprite.setTexture(*playerTexture);
    for (int i = 0; i < 5; i++)
    {
        sprite.setTextureRect(sf::IntRect(shapeSize.x * i, 0, shapeSize.x, shapeSize.y));
        sprite.setScale(sf::Vector2f(3,3));
        result.push_back(sprite);
    }
    return result;
}