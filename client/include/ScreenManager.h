#pragma once

#include "cScreen.h"

typedef std::unique_ptr<cScreen> ScreenState;

class ScreenManager
{
private:
    ScreenState toAdd;
    ScreenState current;
public:
    ScreenManager();
    ~ScreenManager() {};
    void changeScreen(ScreenState newScreen);
    void updateManager();
    ScreenState & getCurrent();
};
