#pragma once
#include <string>
#include "SFML/Graphics.hpp"

// static const int sWidth= sf::VideoMode::getDesktopMode().width;
// static const int sHeight= sf::VideoMode::getDesktopMode().height;
static const int sWidth = 1280;
static const int sHeight = 720;

#define SERVER_IP //Add server ip
#define SPLASH_TIME 1.0f

#define PLAYER_SPEED 4.0f
#define PLAYER_RELOAD 0.6f

#define ENEMY_SPAWN 1.2f
#define ENEMY_SPEED 4.0f

#define PLAYER_MISSILE_SPEED 10.0f
static const std::string server_hostname = "127.0.0.1";
static const unsigned short server_port = 6666;

#define SPLASH_TIME 4.0f
