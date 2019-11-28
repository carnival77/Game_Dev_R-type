#pragma once
#include "App.h"
#include "Screens.h"

class Splash: public cScreen
{
private:
    AppDataRef data;
    sf::Clock clock;
	sf::Sprite background;

    void processEvents();
    void update();
    void render();
    void loadTextures();
public:
    Splash(AppDataRef data);
    ~Splash(){};

    void run();
    
};