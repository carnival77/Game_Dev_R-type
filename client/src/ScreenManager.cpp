#include "ScreenManager.h"

ScreenManager::ScreenManager() 
{ 
    toAdd = nullptr; 
    current = nullptr;
};


void ScreenManager::changeScreen(ScreenState newScreen)
{
    toAdd = std::move(newScreen);
}

void ScreenManager::updateManager()
{
    if (toAdd != nullptr)
    {
        current = std::move(toAdd);
        toAdd = nullptr;
    }    
}


ScreenState & ScreenManager::getCurrent()
{
    return current;
}