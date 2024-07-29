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
#include "../../../TextureCubeRenderer.h"
#define LOG_TAG "NativeBridge"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)



Renderer *renderer = nullptr;
static AAssetManager *assetManager = nullptr;


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_initAssetManager(JNIEnv *env, jobject instance, jobject _assetManager) {

    assetManager = AAssetManager_fromJava(env, _assetManager);

}

extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onSurfaceCreated(JNIEnv * env, jobject obj)
{

    //renderer->onSurfaceCreated();

}

extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onSurfaceChanged(JNIEnv * env, jobject obj, jint width, jint height)
{

    renderer = new TextureCubeRenderer(assetManager);
    renderer->onSurfaceChanged(width, height);

}


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_onDrawFrame(JNIEnv * env, jobject obj)
{

    renderer->onDrawFrame();

}




