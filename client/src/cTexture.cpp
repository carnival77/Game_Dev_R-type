#include "cTexture.h"

void cTexture::load(const std::string & id, const std::string &filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);
    textureMap[id] = texture;
}

sf::Texture& cTexture::get(const std::string &id) 
{
    return textureMap.at(id);
}