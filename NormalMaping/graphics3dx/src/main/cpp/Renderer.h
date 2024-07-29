//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#ifndef OPENGL3D_RENDERER_H
#define OPENGL3D_RENDERER_H

#include <android/asset_manager.h>

class Renderer {

public:

    virtual void onDrawFrame() = 0;
    virtual void onSurfaceCreated() = 0;
    virtual void onSurfaceChanged(int width, int height) = 0;

    bool init = false;

};



#endif //OPENGL3D_RENDERER_H
