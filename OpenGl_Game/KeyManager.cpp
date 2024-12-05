// KeyManager.cpp
#include "KeyManager.h"

void KeyManager::KeyDown(unsigned char key)
{
    keyStates[key] = true;
}

void KeyManager::KeyUp(unsigned char key)
{
    keyStates[key] = false;
}

bool KeyManager::IsKeyPressed(unsigned char key) const {
    auto it = keyStates.find(key);
    if (it != keyStates.end())
    {
        return it->second;
    }
    return false;
}