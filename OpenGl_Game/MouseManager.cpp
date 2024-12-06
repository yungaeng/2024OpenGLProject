#include "MouseManager.h"

MouseManager::MouseManager() : lastX(0), lastY(0), firstMouse(true) {}

void MouseManager::MouseDown(int button) {
    mouseStates[button] = true;
}

void MouseManager::MouseUp(int button) {
    mouseStates[button] = false;
}

bool MouseManager::IsButtonPressed(int button) const {
    auto it = mouseStates.find(button);
    if (it != mouseStates.end()) {
        return it->second;
    }
    return false;
}

void MouseManager::MouseMove(float xpos, float ypos, int windowWidth, int windowHeight) {
    // 마우스 위치를 윈도우 크기 내로 제한
    
  

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos; // y-coordinates are inverted
    lastX = xpos;
    lastY = ypos;

    // Convert to OpenGL coordinates
    xpos = (2.0f * xpos) / windowWidth - 1.0f;
    ypos = 1.0f - (2.0f * ypos) / windowHeight;

    currentX = xpos;
    currentY = ypos;
}

float MouseManager::GetXOffset() const {
    return xoffset;
}

float MouseManager::GetYOffset() const {
    return yoffset;
}

float MouseManager::GetCurrentX() const {
    return currentX;
}

float MouseManager::GetCurrentY() const {
    return currentY;
}

