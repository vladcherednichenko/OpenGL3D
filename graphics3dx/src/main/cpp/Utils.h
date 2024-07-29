//
// Created by Vladyslav Cherednichenko on 27.07.2024.
//

#ifndef OPENGL3D_UTILS_H
#define OPENGL3D_UTILS_H

#include <GLES3/gl3.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define LOG_TAG "Utils"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

static GLuint loadTextureFromAsset(AAssetManager* assetManager, const char* filename) {
    AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_STREAMING);
    if (!asset) {
        LOGI("Failed to open asset: %s", filename);
        return 0;
    }

    off_t fileSize = AAsset_getLength(asset);
    unsigned char* fileData = new unsigned char[fileSize];
    AAsset_read(asset, fileData, fileSize);
    AAsset_close(asset);

    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory(fileData, fileSize, &width, &height, &channels, 4); // Force 4 channels (RGBA)

    delete[] fileData;

    if (!pixels) {
        LOGI("Failed to load texture: %s", filename);
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(pixels);

    return textureID;
}

static GLuint loadSimpleTexture() {
    /* Texture Object Handle. */
    GLuint textureId;
    /* 3 x 3 Image,  R G B A Channels RAW Format. */
    GLubyte pixels[9 * 4] =
            {
                    18, 140, 171, 255, /* Some Colour Bottom Left. */
                    143, 143, 143, 255, /* Some Colour Bottom Middle. */
                    255, 255, 255, 255, /* Some Colour Bottom Right. */
                    255, 255, 0, 255, /* Yellow Middle Left. */
                    0, 255, 255, 255, /* Some Colour Middle. */
                    255, 0, 255, 255, /* Some Colour Middle Right. */
                    255, 0, 0, 255, /* Red Top Left. */
                    0, 255, 0, 255, /* Green Top Middle. */
                    0, 0, 255, 255, /* Blue Top Right. */
            };

    /* Use tightly packed data. */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    /* Generate a texture object. */
    glGenTextures(1, &textureId);
    /* Activate a texture. */
    glActiveTexture(GL_TEXTURE0);
    /* Bind the texture object. */
    glBindTexture(GL_TEXTURE_2D, textureId);
    /* Load the texture. */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 3, 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    /* Set the filtering mode. */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return textureId;
}

#endif //OPENGL3D_UTILS_H
