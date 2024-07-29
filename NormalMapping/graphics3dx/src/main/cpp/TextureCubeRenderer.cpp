//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#include <GLES3/gl3.h>
#include "TextureCubeRenderer.h"
#include "shaders/Shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Utils.h"
#include <string>


bool TextureCubeRenderer::setupGraphics(int width, int height)
{

    shader = new Shader(assetManager, "shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");

    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    projectMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    //textureId = loadSimpleTexture();
    textureId = loadNormalMapTexture(assetManager, "texture/normalMap256.raw");

    //return true;
    if(textureId == 0)
    {
        return false;
    }
    else
    {
        return true;
    }

}


void TextureCubeRenderer::update() {

    modelViewMatrix = glm::mat4(1.0f);
    modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
    modelViewMatrix = glm::rotate(modelViewMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

    shader->use();
    shader->setupAttributes(
            cubeVertices,
            textureCords,
            colour,
            normals,
            biNormals,
            tangents);
    shader->setupUniforms(projectMatrix, modelViewMatrix);
    angle += 1;
    if (angle > 360)
    {
        angle -= 360;
    }

}

void TextureCubeRenderer::onDrawFrame() {

    update();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, &indicies);

}

void TextureCubeRenderer::onSurfaceCreated() {



}

void TextureCubeRenderer::onSurfaceChanged(int width, int height) {

    setupGraphics(width, height);

}

void TextureCubeRenderer::initCubeData() {


}

