#pragma once
#include "constants.h"
#include "ScreenManager.h"
#include "cTexture.h"
#include <memory>
#include <string>

struct AppData
	{
		ScreenManager manager;
		sf::RenderWindow window;
		cTexture textures;
	};

typedef std::shared_ptr<AppData> AppDataRef;


class App
{
private:
    AppDataRef data = std::make_shared<AppData>();
public:
    App(int width, int height, std::string title);
    ~App(){};
    void init();
};
