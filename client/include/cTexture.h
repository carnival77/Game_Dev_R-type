#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Textures
{
    enum ID { Players, RedPlane, PlayerMissile, GameBackground};
}

class cTexture
{
private:
    std::map<Textures::ID, sf::Texture> textureMap;
public:
    cTexture(){};
    sf::Texture& get(Textures::ID id);
    void load(Textures::ID id, const std::string &filename);
};