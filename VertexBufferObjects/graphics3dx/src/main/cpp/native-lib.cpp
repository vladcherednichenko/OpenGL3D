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
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <swappy/swappyGL.h>
#include <swappy/swappyGL_extra.h>

#define LOG_TAG "NativeBridge"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static EGLDisplay display = EGL_NO_DISPLAY;
static EGLContext context = EGL_NO_CONTEXT;
static EGLSurface surface = EGL_NO_SURFACE;
static ANativeWindow* window = nullptr;
static bool running = false;

enum DisplaySwapInterval : uint64_t {
    /** 165 frames per second swap interval */
    kDisplay_Swap_Interval_165FPS = 6060606L,
    /** 120 frames per second swap interval */
    kDisplay_Swap_Interval_120FPS = 8333333L,
    /** 90 frames per second swap interval */
    kDisplay_Swap_Interval_90FPS = 11111111L,
    /** 60 frames per second swap interval */
    kDisplay_Swap_Interval_60FPS = 16666667L,
    /** 45 frames per second swap interval */
    kDisplay_Swap_Interval_45FPS = 22222222L,
    /** 30 frames per second swap interval */
    kDisplay_Swap_Interval_30FPS = 33333333L
};

Renderer *renderer = nullptr;

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
EGLint format;
EGLint contextAttrs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,  // OpenGL ES 2.0
        EGL_NONE
};

void gameLoop() {

    eglMakeCurrent(display, surface, surface, context);

    int width = ANativeWindow_getWidth(window);
    int height = ANativeWindow_getHeight(window);

    renderer->onSurfaceChanged(width, height);

    while (running) {

        renderer->onDrawFrame();
        SwappyGL_swap(display, surface);

    }
}


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_nativeInit(JNIEnv *env, jobject obj, jobject activity, jobject surfaceObj) {
    if (window) {
        ANativeWindow_release(window);
    }

    window = ANativeWindow_fromSurface(env, surfaceObj);

    // Get JavaVM reference (optional)
    JavaVM *vm;
    env->GetJavaVM(&vm);

    // Store the activity reference globally if needed
    jobject globalActivity = env->NewGlobalRef(activity);

    // Initialize Swappy with jactivity
    SwappyGL_init(env, globalActivity);
    SwappyGL_setSwapIntervalNS(kDisplay_Swap_Interval_120FPS);
    SwappyGL_setAutoSwapInterval(false);

    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (!eglInitialize(display, nullptr, nullptr)) {
        LOGE("Failed to initialize EGL!");
        return;
    }
    eglChooseConfig(display, attributes, &config, 1, &numConfigs);

    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    ANativeWindow_setBuffersGeometry(window, 0, 0, format);

    context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttrs);
    surface = eglCreateWindowSurface(display, config, window, nullptr);

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
Java_site_pixio_graphics3dx_NativeBridge_nativeResize(JNIEnv *env, jobject obj, jint width, jint height) {}


extern "C"
JNIEXPORT void JNICALL
Java_site_pixio_graphics3dx_NativeBridge_initAssetManager(JNIEnv *env, jobject instance, jobject _assetManager) {

    renderer = new TextureCubeRenderer(AAssetManager_fromJava(env, _assetManager));

}





