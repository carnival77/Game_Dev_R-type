#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
using namespace std;

vector<sf::Sprite> loadPlayerShip();
vector<sf::Sprite> loadEnemyShip();
sf::Sprite loadPlayerMissile();
