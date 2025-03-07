//
// Created by Vladyslav Cherednichenko on 10.02.2025.
//

#ifndef OPENGL3D_FPSCOUNTER_H
#define OPENGL3D_FPSCOUNTER_H

#include <chrono>

class FpsCounter {

public:

    static FpsCounter* getInstance();

    float getFps();

private:

    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime;
    int frames = 0;
    float fps = 0;


};


#endif //OPENGL3D_FPSCOUNTER_H
