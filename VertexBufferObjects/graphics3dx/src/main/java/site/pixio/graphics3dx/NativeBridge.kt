package site.pixio.graphics3dx

import android.content.res.AssetManager
import android.view.Surface


object NativeBridge {

    init {
        System.loadLibrary("native-lib")
    }


    external fun initAssetManager(assetManager: AssetManager)
    external fun nativeInit(surface: Surface)
    external fun nativeDestroy()
    external fun nativeResize(width: Int, height: Int)

}