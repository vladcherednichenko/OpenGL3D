#include <jni.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <thread>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <android/asset_manager_jni.h>
#include "glm/gtc/type_ptr.hpp"
#include "Renderer.h"
#include "textureCube/TextureCubeRenderer.h"

#define LOG_TAG "NativeBridge"


GLfloat verticies[] = { 1.0f,  1.0f, -1.0f, /* Back. */
                        -1.0f,  1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,
                        -1.0f, -1.0f, -1.0f,
                        0.0f,  0.0f, -2.0f,
                        -1.0f,  1.0f,  1.0f, /* Front. */
                        1.0f,  1.0f,  1.0f,
                        -1.0f, -1.0f,  1.0f,
                        1.0f, -1.0f,  1.0f,
                        0.0f,  0.0f,  2.0f,
                        -1.0f,  1.0f, -1.0f, /* Left. */
                        -1.0f,  1.0f,  1.0f,
                        -1.0f, -1.0f, -1.0f,
                        -1.0f, -1.0f,  1.0f,
                        -2.0f,  0.0f,  0.0f,
                        1.0f,  1.0f,  1.0f, /* Right. */
                        1.0f,  1.0f, -1.0f,
                        1.0f, -1.0f,  1.0f,
                        1.0f, -1.0f, -1.0f,
                        2.0f,  0.0f,  0.0f,
                        -1.0f, -1.0f,  1.0f, /* Bottom. */
                        1.0f, -1.0f,  1.0f,
                        -1.0f, -1.0f, -1.0f,
                        1.0f, -1.0f, -1.0f,
                        0.0f, -2.0f,  0.0f,
                        -1.0f,  1.0f, -1.0f, /* Top. */
                        1.0f,  1.0f, -1.0f,
                        -1.0f,  1.0f,  1.0f,
                        1.0f,  1.0f,  1.0f,
                        0.0f,  2.0f,  0.0f
};

GLfloat colour[] = {1.0f, 0.0f, 0.0f, /* Back. */
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, /* Front. */
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, /* Left. */
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 0.0f, /* Right. */
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 1.0f, /* Bottom. */
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f, /* Top. */
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f
};


GLfloat normals[] = { 1.0f,  1.0f, -1.0f, /* Back. */
                      -1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      0.0f,  0.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f, /* Front. */
                      1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                      0.0f,  0.0f,  1.0f,
                      -1.0f,  1.0f, -1.0f, /* Left. */
                      -1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f,  1.0f,
                      -1.0f,  0.0f,  0.0f,
                      1.0f,  1.0f,  1.0f, /* Right. */
                      1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f,  0.0f,  0.0f,
                      -1.0f, -1.0f,  1.0f, /* Bottom. */
                      1.0f, -1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      0.0f, -1.0f,  0.0f,
                      -1.0f,  1.0f, -1.0f, /* Top. */
                      1.0f,  1.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      0.0f,  1.0f,  0.0f
};

//GLushort indices[] = {0,  2,  4,  0,  4,  1,  1,  4,  3,  2,  3,  4,  /* Back. */
//                      5,  7,  9,  5,  9,  6,  6,  9,  8,  7,  8,  9,  /* Front. */
//                      10, 12, 14, 10, 14, 11, 11, 14, 13, 12, 13, 14, /* Left. */
//                      15, 17, 19, 15, 19, 16, 16, 19, 18, 17, 18, 19, /* Right. */
//                      20, 22, 24, 20, 24, 21, 21, 24, 23, 22, 23, 24, /* Bottom. */
//                      25, 27, 29, 25, 29, 26, 26, 29, 28, 27, 28, 29  /* Top. */
//};

Renderer *renderer = nullptr;



extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_initAssetManager(JNIEnv *env, jobject instance, jobject _assetManager) {

    renderer = new TextureCubeRenderer(AAssetManager_fromJava(env, _assetManager));

}

extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onSurfaceCreated(JNIEnv * env, jobject obj)
{

    renderer->onSurfaceCreated();

}

extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onSurfaceChanged(JNIEnv * env, jobject obj, jint width, jint height)
{

    renderer->onSurfaceChanged(width, height);

}


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onDrawFrame(JNIEnv * env, jobject obj)
{

    renderer->onDrawFrame();

}




