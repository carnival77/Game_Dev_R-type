#include "background.h"


Background::Background(std::string textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        // err
    }
    //texture.setSmooth(true);
    //texture.setRepeated(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height));
}


Background::~Background() {

}

void Background::scroll(float speed)
{
    //sprite.setTextureRect(sprite.getPosition().x - speed, sprite.getPosition().y);
    //sprite.move(-speed,0);
}
