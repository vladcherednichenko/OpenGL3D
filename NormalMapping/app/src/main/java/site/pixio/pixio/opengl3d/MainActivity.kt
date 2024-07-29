package site.pixio.pixio.opengl3d

import android.annotation.SuppressLint
import android.os.Bundle
import android.speech.tts.TextToSpeech.EngineInfo
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.viewinterop.AndroidView
import site.pixio.graphics3dx.Engine
import site.pixio.pixio.opengl3d.ui.theme.Opengl3DTheme

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

        enableEdgeToEdge()

    }
}
