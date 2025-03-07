package site.pixio.pixio.opengl3d

import android.annotation.SuppressLint
import android.os.Build
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.annotation.RequiresApi
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.ui.Modifier
import androidx.compose.ui.viewinterop.AndroidView
import androidx.core.text.layoutDirection
import site.pixio.graphics3dx.Engine
import site.pixio.pixio.opengl3d.ui.theme.Opengl3DTheme
import java.text.DateFormat
import java.text.SimpleDateFormat
import java.time.LocalDate
import java.time.format.DateTimeFormatter
import java.time.format.FormatStyle
import java.util.Locale

class MainActivity : ComponentActivity() {
    @SuppressLint("UnusedMaterial3ScaffoldPaddingParameter")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
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


        val display = windowManager.defaultDisplay
        val refreshRate = display.refreshRate
        Log.d("FPS", "Current Refresh Rate: $refreshRate Hz")

        enableEdgeToEdge()

    }

}


