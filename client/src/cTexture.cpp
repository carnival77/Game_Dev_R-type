#include "cTexture.h"

void cTexture::load(Textures::ID id, const std::string &filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);
    textureMap[id] = texture;
}

sf::Texture& cTexture::get(Textures::ID id) 
{
    return textureMap.at(id);
}