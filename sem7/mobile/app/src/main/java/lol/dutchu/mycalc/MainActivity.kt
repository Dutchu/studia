package lol.dutchu.mycalc

import android.os.Bundle
import android.widget.Button
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
import androidx.fragment.app.FragmentManager
import androidx.fragment.app.FragmentTransaction
import androidx.lifecycle.ViewModelProvider
import lol.dutchu.mycalc.ui.theme.MyCalcTheme

class MainActivity : ComponentActivity()  {

    private lateinit var myViewModel: MyViewModel
    val fragmentManager = supportFragmentManager
    private val button = findViewById<Button>(R.id.button)

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MyCalcTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }

        myViewModel = ViewModelProvider(this)[MyViewModel::class.java]
        button.setOnClickListener(this)

        var fm: FragmentManager = get
        var ft: FragmentTransaction = fm.beginTransaction()
    }

    override fun onClick(view: View?) {
        when(view?.id) {

        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    MyCalcTheme {
        Greeting("Android")
    }
}