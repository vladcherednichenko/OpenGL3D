package site.pixio.graphics3dx

import android.app.Activity
import android.content.res.AssetManager
import android.view.Surface


object NativeBridge {

    init {
        System.loadLibrary("native-lib")
    }


    external fun initAssetManager(assetManager: AssetManager)
    external fun nativeInit(activity: Activity, surface: Surface)
    external fun nativeDestroy()
    external fun nativeResize(width: Int, height: Int)

}