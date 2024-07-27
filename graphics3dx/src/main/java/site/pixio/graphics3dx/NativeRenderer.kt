package site.pixio.graphics3dx

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class NativeRenderer : GLSurfaceView.Renderer {

    override fun onDrawFrame(gl: GL10) {
        NativeBridge.onDrawFrame()
    }

    override fun onSurfaceCreated(p0: GL10?, p1: EGLConfig?) {
        NativeBridge.onSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        NativeBridge.onSurfaceChanged(width, height)
    }

}