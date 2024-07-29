//
// Created by Vladyslav Cherednichenko on 24.07.2024.
//

#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include <android/log.h>
#include <fstream>
#include <sstream>
#include <iostream>

#define LOG_TAG "NativeLib"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

Shader::Shader(AAssetManager *assetManager, const std::string &vertexPath,
               const std::string &fragmentPath) {

    std::string vertexCode = readFile(assetManager, vertexPath);
    std::string fragmentCode = readFile(assetManager, fragmentPath);

    program = createProgram(vertexCode, fragmentCode);
    if (!program)
    {
        LOGI("Could not create program");
        return;
    }

    vertexPositionLocation = glGetAttribLocation(program, VERTEX_POSITION_ATTRIBUTE_NAME);
    vertexTextureCordsLocation = glGetAttribLocation(program, VERTEX_TEXTURE_CORDS_ATTRIBUTE_NAME);
    vertexColourLocation = glGetAttribLocation(program, VERTEX_COLOUR_ATTRIBUTE_NAME);
    vertexNormalLocation = glGetAttribLocation(program, VERTEX_NORMAL_ATTRIBUTE_NAME);
    projectionLocation = glGetUniformLocation(program, UNIFORM_PROJECTION_NAME);
    modelViewLocation = glGetUniformLocation(program, UNIFORM_MODEL_VIEW_NAME);
    samplerLocation = glGetUniformLocation(program, UNIFORM_TEXTURE_NAME);

}

std::string Shader::readFile(AAssetManager* assetManager, const std::string& filePath) {
    AAsset* asset = AAssetManager_open(assetManager, filePath.c_str(), AASSET_MODE_BUFFER);
    if (asset == nullptr) {
        std::cerr << "Failed to open asset: " << filePath << std::endl;
        return "";
    }

    off_t assetLength = AAsset_getLength(asset);
    std::string fileContent;
    fileContent.resize(assetLength);

    AAsset_read(asset, &fileContent[0], assetLength);
    AAsset_close(asset);

    return fileContent;
}

GLuint Shader::loadShader(GLenum shaderType, const std::string& shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        const char* sourceCStr = shaderSource.c_str();
        glShaderSource(shader, 1, &sourceCStr, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char * buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGI("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint Shader::createProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }
    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);
        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGI("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }

    return program;

}

void Shader::use() {

    glUseProgram(program);

}

//void Shader::setupAttributes(const GLfloat *vertexData, const GLfloat *colorData, const GLfloat *normalData) {
//
//    glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertexData);
//    glEnableVertexAttribArray(vertexPositionLocation);
//    glVertexAttribPointer(vertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, colorData);
//    glEnableVertexAttribArray(vertexColourLocation);
//    glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, normalData);
//    glEnableVertexAttribArray(vertexNormalLocation);
//
//}

void Shader::setupAttributes(const GLfloat* vertexData, const GLfloat* textureData, const GLfloat* normalData) {

    glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, vertexData);
    glEnableVertexAttribArray(vertexPositionLocation);
    glVertexAttribPointer(vertexTextureCordsLocation, 2, GL_FLOAT, GL_FALSE, 0, textureData);
    glEnableVertexAttribArray(vertexTextureCordsLocation);
    glVertexAttribPointer(vertexNormalLocation, 3, GL_FLOAT, GL_FALSE, 0, normalData);
    glEnableVertexAttribArray(vertexNormalLocation);

}

void Shader::setupUniforms(const glm::mat4 &projection, const glm::mat4 &modelView) {

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelView));
    /* Set the sampler texture unit to 0. */
    glUniform1i(samplerLocation, 0);

}

