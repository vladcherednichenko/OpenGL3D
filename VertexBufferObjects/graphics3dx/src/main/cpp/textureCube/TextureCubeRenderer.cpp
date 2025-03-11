//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#include <GLES3/gl3.h>
#include "TextureCubeRenderer.h"
#include "shaders/Shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "../Utils.h"
#include <string>
#include "FpsCounter.h"


bool TextureCubeRenderer::setupGraphics(int width, int height)
{
    shader = new Shader(assetManager, "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    projectMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);


    static GLuint vboBufferIds[2];
    // crate 2 buffers
    glGenBuffers(2, vboBufferIds);
    // array buffer is used to store vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, vboBufferIds[0]);
    // element array buffer is used to store indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboBufferIds[1]);


    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, cubeVertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBufferSize, indices, GL_STATIC_DRAW);

    shader->use();
    shader->setupAttributes();

    return true;

}

std::chrono::duration tick = std::chrono::milliseconds(30);
auto lastUpdate = std::chrono::high_resolution_clock::now();

void TextureCubeRenderer::update() {

    modelViewMatrix = glm::mat4(1.0f);
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->setupUniforms(projectMatrix, modelViewMatrix);

    auto currentTime = std::chrono::high_resolution_clock::now();
    if(currentTime - lastUpdate >= tick)
    {
        lastUpdate = currentTime;
        angle += 0.5;
        if (angle > 360)
        {
            angle -= 360;
        }
    }

}

void TextureCubeRenderer::onDrawFrame() {

    update();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    LOGI("FPS: %f", FpsCounter::getInstance()->getFps());

}

void TextureCubeRenderer::onSurfaceCreated() {}

void TextureCubeRenderer::onSurfaceChanged(int width, int height) {

    setupGraphics(width, height);

}

