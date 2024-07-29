//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#ifndef OPENGL3D_TEXTURECUBERENDERER_H
#define OPENGL3D_TEXTURECUBERENDERER_H

#include "src/main/cpp/Renderer.h"
#include "shaders/Shader.h"

class TextureCubeRenderer : public Renderer {

public:

    TextureCubeRenderer(AAssetManager* assetManager) {
        this->assetManager = assetManager;
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
    const GLfloat cubeVertices[24*3] = {-1.0f,  1.0f, -1.0f, /* Back. */
                                   1.0f,  1.0f, -1.0f,
                                   -1.0f, -1.0f, -1.0f,
                                   1.0f, -1.0f, -1.0f,
                                   -1.0f,  1.0f,  1.0f, /* Front. */
                                   1.0f,  1.0f,  1.0f,
                                   -1.0f, -1.0f,  1.0f,
                                   1.0f, -1.0f,  1.0f,
                                   -1.0f,  1.0f, -1.0f, /* Left. */
                                   -1.0f, -1.0f, -1.0f,
                                   -1.0f, -1.0f,  1.0f,
                                   -1.0f,  1.0f,  1.0f,
                                   1.0f,  1.0f, -1.0f, /* Right. */
                                   1.0f, -1.0f, -1.0f,
                                   1.0f, -1.0f,  1.0f,
                                   1.0f,  1.0f,  1.0f,
                                   -1.0f, 1.0f, -1.0f, /* Top. */
                                   -1.0f, 1.0f,  1.0f,
                                   1.0f, 1.0f,  1.0f,
                                   1.0f, 1.0f, -1.0f,
                                   -1.0f, - 1.0f, -1.0f, /* Bottom. */
                                   -1.0f,  -1.0f,  1.0f,
                                   1.0f, - 1.0f,  1.0f,
                                   1.0f,  -1.0f, -1.0f
    };

    GLfloat textureCords[24*2] = {
            0.75f, 0.333f, /* Back. */
            0.5f, 0.333f,
            0.75f, 0.666f,
            0.5f, 0.666f,

            0.0f, 0.333f, /* Front. */
            0.25f, 0.333f,
            0.0f, 0.666f,
            0.25f, 0.666f,

            0.75f, 0.333f, /* Left. */
            0.75f, 0.666f,
            1.0f, 0.666f,
            1.0f, 0.333f,

            0.5f, 0.333f, /* Right. */
            0.5f, 0.666f,
            0.25f, 0.666f,
            0.25f, 0.333f,

            0.25f, 0.0f, /* Top. */
            0.25f, 0.333f,
            0.5f, 0.333f,
            0.5f, 0.0f,

            0.25f, 1.0f, /* Bottom. */
            0.25f, 0.666f,
            0.5f, 0.666f,
            0.5f, 1.0f
    };

    GLushort indices[36] = {0, 2, 3, 0, 1, 3, 4, 6, 7, 4, 5, 7, 8, 9, 10, 11, 8, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22};

    void update();
    bool setupGraphics(int width, int height);


};

#endif //OPENGL3D_TEXTURECUBERENDERER_H
