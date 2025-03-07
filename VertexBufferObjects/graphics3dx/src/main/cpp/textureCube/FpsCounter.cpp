//
// Created by Vladyslav Cherednichenko on 10.02.2025.
//

#include "FpsCounter.h"

FpsCounter *FpsCounter::getInstance() {
    static FpsCounter instance;
    return &instance;
}

float FpsCounter::getFps() {

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

    if (duration > 1000)
    {
        fps = frames * 1000.0f / duration;
        frames = 0;
        lastTime = currentTime;
    }

    frames++;

    return fps;
}
