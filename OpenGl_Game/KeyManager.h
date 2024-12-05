// KeyManager.h
#pragma once
#include <unordered_map>

class KeyManager {
public:
    static KeyManager& getInstance() {
        static KeyManager instance;
        return instance;
    }
    void KeyDown(unsigned char key);
    void KeyUp(unsigned char key);
    bool IsKeyPressed(unsigned char key) const;

private:
    std::unordered_map<unsigned char, bool> keyStates;
};


