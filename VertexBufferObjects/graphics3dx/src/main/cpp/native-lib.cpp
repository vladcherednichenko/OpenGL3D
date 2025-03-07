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
#include "Utils.h"
#include "textureCube/FpsCounter.h"

#define LOG_TAG "NativeBridge"

#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>



#include <jni.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <android/log.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <thread>
#include <chrono>

#define  LOG_TAG    "OpenGL"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static EGLDisplay display = EGL_NO_DISPLAY;
static EGLContext context = EGL_NO_CONTEXT;
static EGLSurface surface = EGL_NO_SURFACE;
static ANativeWindow* window = nullptr;
static bool running = false;

Renderer *renderer = nullptr;

float FPS = 90.0f;
std::chrono::duration frameTime = (1000.0f / FPS) * std::chrono::milliseconds(1);

// Choose an EGL config
EGLint attributes[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,  // Ensure color depth is at least 8-bit per channel
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,  // Ensure transparency support
        EGL_DEPTH_SIZE, 16, // 16-bit depth buffer (change to 24 if needed)
        EGL_STENCIL_SIZE, 8, // Stencil buffer support
        EGL_NONE
};
EGLConfig config;
EGLint numConfigs;

EGLint contextAttrs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,  // OpenGL ES 2.0
        EGL_NONE
};

void doFrame() {

    renderer->onDrawFrame();

    //LOGI("FPS: %f", FpsCounter::getInstance()->getFps());
    eglSwapBuffers(display, surface);
}


void gameLoop() {

    eglMakeCurrent(display, surface, surface, context);

    int width = ANativeWindow_getWidth(window);
    int height = ANativeWindow_getHeight(window);

    renderer->onSurfaceChanged(width, height);

    eglSwapInterval(display, 0);

    while (running) {

        doFrame();

        // Sleep to achieve target FPS
        std::this_thread::sleep_for(frameTime);
    }
}




extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_nativeInit(JNIEnv *env, jobject obj, jobject surfaceObj) {
    if (window) {
        ANativeWindow_release(window);
    }

    window = ANativeWindow_fromSurface(env, surfaceObj);
    if (!window) {
        LOGE("Failed to get native window!");
        return;
    }
    LOGI("ANativeWindow acquired successfully.");

    if (display == EGL_NO_DISPLAY) {
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY || !eglInitialize(display, nullptr, nullptr)) {
            LOGE("EGL Display initialization failed!");
            return;
        }
    }

    EGLint numConfigs;
    if (!eglChooseConfig(display, attributes, &config, 1, &numConfigs) || numConfigs == 0) {
        LOGE("Failed to choose a valid EGL config!");
        return;
    }

    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    if (context == EGL_NO_CONTEXT) {
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttrs);
        if (context == EGL_NO_CONTEXT) {
            LOGE("Failed to create EGL context!");
            return;
        }
    }

    if (surface != EGL_NO_SURFACE) {
        eglDestroySurface(display, surface);
    }

    surface = eglCreateWindowSurface(display, config, window, nullptr);
    if (surface == EGL_NO_SURFACE) {
        EGLint error = eglGetError();
        LOGE("Failed to create EGL surface! Error: 0x%X", error);
        return;
    }
    LOGI("EGL surface created successfully.");


    // Release EGL context from the main thread
    eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);


    running = true;

    renderer->onSurfaceCreated();

    std::thread(gameLoop).detach();
}


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_nativeDestroy(JNIEnv *env, jobject obj) {
    // Stop the game loop
    running = false;

    // Clean up EGL
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(display, surface);
        eglDestroyContext(display, context);
        eglTerminate(display);
    }

    LOGI("EGL context destroyed!");
}

extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_nativeResize(JNIEnv *env, jobject obj, jint width, jint height) {
    //renderer->onSurfaceChanged(width, height);
}



extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_initAssetManager(JNIEnv *env, jobject instance, jobject _assetManager) {

    renderer = new TextureCubeRenderer(AAssetManager_fromJava(env, _assetManager));

}

//extern "C"
//JNIEXPORT void JNICALL
//Java_site_pixio_graphics3dx_NativeBridge_onSurfaceCreated(JNIEnv * env, jobject obj)
//{
//
//    renderer->onSurfaceCreated();
//
//}

//extern "C"
//JNIEXPORT void JNICALL
//Java_site_pixio_graphics3dx_NativeBridge_onSurfaceChanged(JNIEnv * env, jobject obj, jint width, jint height)
//{
//
//    renderer->onSurfaceChanged(width, height);
//
//}


//extern "C"
//JNIEXPORT void JNICALL
//Java_site_pixio_graphics3dx_NativeBridge_onDrawFrame(JNIEnv * env, jobject obj)
//{
//
//    renderer->onDrawFrame();
//
//}




