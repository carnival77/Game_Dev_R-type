#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class cTexture
{
private:
    std::map<std::string , sf::Texture> textureMap;
public:
    cTexture(){};
    sf::Texture& get(const std::string & id);
    void load(const std::string& id, const std::string &filename);
};