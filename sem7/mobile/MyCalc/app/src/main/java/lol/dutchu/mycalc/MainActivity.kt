package lol.dutchu.mycalc

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
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
import lol.dutchu.mycalc.ui.theme.MyCalcTheme

class MainActivity : ComponentActivity() {
    private var counter = 0

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val displayText = findViewById<TextView>(R.id.displayText)
        val buttonIncrease = findViewById<Button>(R.id.button_increase)
        val buttonDecrease = findViewById<Button>(R.id.button_decrease)

        fun updateDisplay() {
            displayText.text = counter.toString()
        }

        buttonIncrease.setOnClickListener {
            counter++
            updateDisplay()
        }

        buttonDecrease.setOnClickListener {
            counter--
            updateDisplay()
        }

        updateDisplay()
    }
}