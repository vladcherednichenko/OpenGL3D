//
// Created by Vladyslav Cherednichenko on 24.07.2024.
//

#ifndef PIXIOR_SHADER_H
#define PIXIOR_SHADER_H

#include <GLES3/gl3.h>
#include <glm/glm.hpp>
#include <android/asset_manager.h>

class Shader {

public:

    const GLchar *VERTEX_POSITION_ATTRIBUTE_NAME = "vertexPosition";
    const GLchar *VERTEX_TEXTURE_CORDS_ATTRIBUTE_NAME = "vertexTextureCord";
    const GLchar *VERTEX_COLOUR_ATTRIBUTE_NAME = "vertexColor";
    const GLchar *VERTEX_NORMAL_ATTRIBUTE_NAME = "vertexNormal";
    const GLchar *VERTEX_TANGENT_ATTRIBUTE_NAME = "vertexTangent";
    const GLchar *VERTEX_BI_NORMAL_ATTRIBUTE_NAME = "vertexBiNormal";


    const GLchar *UNIFORM_PROJECTION_NAME = "projection";
    const GLchar *UNIFORM_MODEL_VIEW_NAME = "modelView";
    const GLchar *UNIFORM_TEXTURE_NAME = "texture";

    GLuint program;
    GLuint vertexLocation;
    GLuint samplerLocation;
    GLuint projectionLocation;
    GLuint modelViewLocation;
    GLuint textureCordLocation;
    GLuint colorLocation;
    GLuint textureId;
    GLuint vertexNormalLocation;
    GLuint tangentLocation;
    GLuint biNormalLocation;

    Shader(AAssetManager* assetManager, const std::string& vertexPath, const std::string& fragmentPath);
    void use();

    void setupAttributes(
            const GLfloat* cubeVertices,
            const GLfloat* textureCords,
            const GLfloat* colour,
            const GLfloat* normals,
            const GLfloat* biNormals,
            const GLfloat* tangents);
    void setupUniforms(const glm::mat4 &projection, const glm::mat4 &modelView);

private:


    GLuint loadShader(GLenum shaderType, const std::string& shaderSource);
    GLuint createProgram(const std::string& vertexSource, const std::string& fragmentSource);
    std::string readFile(AAssetManager* assetManager, const std::string& filePath);

};

#endif //PIXIOR_SHADER_H
