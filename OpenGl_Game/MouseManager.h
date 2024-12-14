#ifndef MOUSEMANAGER_H
#define MOUSEMANAGER_H

#include <unordered_map>

class MouseManager {
public:
    static MouseManager& getInstance() {
        static MouseManager instance;
        return instance;
    }
    MouseManager();

    void MouseDown(int button);
    void MouseUp(int button);
    bool IsButtonPressed(int button) const;
	bool IsLeftButtonPressed() const;
    void MouseMove(float xpos, float ypos, int windowWidth, int windowHeight);

    float GetXOffset() const;
    float GetYOffset() const;
    float GetCurrentX() const;
    float GetCurrentY() const;

private:
    std::unordered_map<int, bool> mouseStates;
    float lastX, lastY;
    float xoffset, yoffset;
    float currentX, currentY;
    bool firstMouse;
};

#endif // MOUSEMANAGER_H

