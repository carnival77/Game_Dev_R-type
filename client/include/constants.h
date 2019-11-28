#pragma once
#include <string>
#include "SFML/Graphics.hpp"

// static const int sWidth= sf::VideoMode::getDesktopMode().width;
// static const int sHeight= sf::VideoMode::getDesktopMode().height;
static const int sWidth = 1280;
static const int sHeight = 720;

static const std::string server_hostname = "127.0.0.1";
static const unsigned short server_port = 6666;

#define SPLASH_TIME 4.0f