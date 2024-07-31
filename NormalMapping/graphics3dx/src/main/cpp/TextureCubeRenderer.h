//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#ifndef OPENGL3D_TEXTURECUBERENDERER_H
#define OPENGL3D_TEXTURECUBERENDERER_H

#include "Renderer.h"
#include "shaders/Shader.h"

class TextureCubeRenderer : public Renderer {

public:

    TextureCubeRenderer(AAssetManager* assetManager) {
        this->assetManager = assetManager;
        initCubeData();
    }

    void onDrawFrame() override ;
    void onSurfaceCreated() override;
    void onSurfaceChanged(int width, int height) override;


private:


    AAssetManager* assetManager = nullptr;
    glm::mat4 projectMatrix = glm::mat4(0.0f);
    glm::mat4 modelViewMatrix = glm::mat4(0.0f);
    Shader* shader = nullptr;
    float fov = 45.0f; // Field of view in degrees
    float zNear = 0.1f;
    float zFar = 100.0f;
    float angle = 0.0f;
    GLuint textureId = 0;

    void update();
    bool setupGraphics(int width, int height);
    void initCubeData();


};

#endif //OPENGL3D_TEXTURECUBERENDERER_H
