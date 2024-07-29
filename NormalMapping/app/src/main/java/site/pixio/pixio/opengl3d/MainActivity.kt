package site.pixio.pixio.opengl3d

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import site.pixio.graphics3dx.Engine
import site.pixio.pixio.opengl3d.ui.theme.Opengl3DTheme
import java.io.File
import java.io.RandomAccessFile

class MainActivity : ComponentActivity() {
    @SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        assetDirectory = applicationContext.getFilesDir().getPath() + "/";
        extractAsset("normalMap256.raw")

        Engine.initialize(this)
        val surfaceView = Engine.getSurfaceView(this)
        setContent {
            Opengl3DTheme {
                AndroidView(
                    factory = { surfaceView },
                    modifier = Modifier.fillMaxSize()
                )
            }
        }

        enableEdgeToEdge()

    }


    var LOGTAG: String = "NormalMapping"
    var assetDirectory: String? = null

    private fun extractAsset(assetName: String) {
        val fileTest = File(assetDirectory + assetName)

        if (fileTest.exists()) {
            Log.d(
                LOGTAG,
                "$assetName already exists no extraction needed\n"
            )
        } else {
            Log.d(
                LOGTAG,
                "$assetName doesn't exist extraction needed \n"
            )
            /* [extractAssetBeginning] */
            /* [tryCatchExtractAsset] */
            try {
                val out = RandomAccessFile(assetDirectory + assetName, "rw")
                val am = applicationContext.resources.assets
                /* [tryCatchExtractAsset] */
                /* [readWriteFile] */
                val inputStream = am.open(assetName)
                val buffer = ByteArray(1024)
                var count = inputStream.read(buffer, 0, 1024)

                while (count > 0) {
                    out.write(buffer, 0, count)
                    count = inputStream.read(buffer, 0, 1024)
                }
                out.close()
                inputStream.close()
            } catch (e: Exception) {
                Log.e(
                    LOGTAG,
                    "Failure in extractAssets(): " + e.toString() + " " + assetDirectory + assetName
                )
            }
            if (fileTest.exists()) {
                Log.d(LOGTAG, "File Extracted successfully")
                /* [readWriteFile] */
            }
        }
    }


}
