package site.pixio.graphics3dx

import android.content.Context
import android.opengl.GLSurfaceView

object Engine {

    fun initialize(context: Context) {

        // Asset manager is needed to load resources from the APK, such as shaders
        NativeBridge.initAssetManager(context.assets)

    }

    fun getSurfaceView(context: Context): GLSurfaceView {
        val glSurfaceView = GLSurfaceView(context)
        glSurfaceView.apply {
            setEGLContextClientVersion(3) // Use OpenGL ES 3.0
            setRenderer(NativeRenderer())
        }
        return glSurfaceView
    }

}