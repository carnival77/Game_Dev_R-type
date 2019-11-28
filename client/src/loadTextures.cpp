#include "loadTextures.h"

vector<sf::Sprite> loadRedShip()
{
    sf::Texture * playerTexture = new sf::Texture;
    playerTexture->loadFromFile("./textures/redEnemyShip.gif");

    sf::Vector2u shapeSize = playerTexture->getSize();
    
    vector<sf::Sprite> result;
    sf::Sprite sprite;
    sprite.setTexture(*playerTexture);
    
    return result;
}
