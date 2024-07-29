package site.pixio.graphics3dx

import android.content.res.AssetManager



object NativeBridge {

    init {
        System.loadLibrary("native-lib")
    }

    external fun initAssetManager(assetManager: AssetManager?)
    external fun onSurfaceCreated()
    external fun onDrawFrame()
    external fun onSurfaceChanged(width: Int, height: Int)

}