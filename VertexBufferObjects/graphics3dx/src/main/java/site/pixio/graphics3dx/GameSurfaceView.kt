package site.pixio.graphics3dx

import android.app.Activity
import android.content.Context
import android.graphics.Color
import android.opengl.EGL14
import android.opengl.EGLConfig
import android.opengl.EGLContext
import android.opengl.EGLDisplay
import android.opengl.EGLSurface
import android.opengl.GLES30
import android.opengl.GLSurfaceView
import android.view.Choreographer
import android.view.Surface
import android.view.SurfaceHolder
import android.view.SurfaceView

class GameSurfaceView(val activity: Activity) : SurfaceView(activity), SurfaceHolder.Callback {

    init {
        holder.addCallback(this)
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        NativeBridge.nativeInit(activity, holder.surface)  // Pass Surface to C++
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        NativeBridge.nativeDestroy()  // Stop rendering
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
        NativeBridge.nativeResize(width, height)
    }


}

