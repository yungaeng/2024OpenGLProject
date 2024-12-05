// TimeManager.h
#pragma once
#include <chrono>

class TimeManager {
public:
    static TimeManager& getInstance() {
        static TimeManager instance;
        return instance;
    }

    void Initialize();
    double GetElapsedTime();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> previousFrameTime;
};

