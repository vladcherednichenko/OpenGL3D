package site.pixio.graphics3dx

import android.content.Context
import android.opengl.GLSurfaceView
import android.view.SurfaceView
import javax.microedition.khronos.egl.EGL10
import javax.microedition.khronos.egl.EGLConfig


object Engine {

    fun initialize(context: Context) {

        // Asset manager is needed to load resources from the APK, such as shaders
        NativeBridge.initAssetManager(context.assets)

    }

    fun getSurfaceView(context: Context): SurfaceView {
        val glSurfaceView = GameSurfaceView(context)
//        glSurfaceView.apply {
//            setEGLContextClientVersion(3) // Use OpenGL ES 3.0

//            setEGLConfigChooser { egl, display ->
//                val attribList = intArrayOf(
//                    EGL10.EGL_RED_SIZE, 8,
//                    EGL10.EGL_GREEN_SIZE, 8,
//                    EGL10.EGL_BLUE_SIZE, 8,
//                    EGL10.EGL_ALPHA_SIZE, 8, // Ensure alpha size if needed
//                    EGL10.EGL_DEPTH_SIZE, 16,
//                    EGL10.EGL_STENCIL_SIZE, 8, // If stencil buffer is needed
//                    EGL10.EGL_SAMPLE_BUFFERS, 0,  // Disable multisampling
//                    EGL10.EGL_SAMPLES, 0,
//                    EGL10.EGL_NONE
//                )
//                val configs: Array<EGLConfig?> = arrayOfNulls<EGLConfig>(1)
//                val numConfigs = IntArray(1)
//                egl.eglChooseConfig(display, attribList, configs, 1, numConfigs)
//                configs[0]
//            }

//            setRenderer(NativeRenderer())
//
//        }


        return glSurfaceView
    }

}