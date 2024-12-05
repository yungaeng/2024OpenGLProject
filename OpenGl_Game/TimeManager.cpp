// TimeManager.cpp
#include "TimeManager.h"

void TimeManager::Initialize() {
    previousFrameTime = std::chrono::high_resolution_clock::now();
}

double TimeManager::GetElapsedTime() {
    auto currentFrameTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentFrameTime - previousFrameTime;
    previousFrameTime = currentFrameTime;
    return elapsedTime.count();
}
