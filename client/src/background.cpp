#include "background.h"


Background::Background(std::string textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        // err
    }
    texture.setSmooth(true);

    sprite.setTexture(texture);
}


Background::~Background() {

}