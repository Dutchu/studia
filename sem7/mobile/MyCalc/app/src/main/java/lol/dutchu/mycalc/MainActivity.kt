package lol.dutchu.mycalc

import android.content.res.Configuration
import android.os.Bundle
import android.view.View
import android.widget.HorizontalScrollView
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.Observer
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : ComponentActivity() {
    private var result = 0
    private val stack = MutableLiveData<MutableList<Int>>(mutableListOf())
    private val rowsNum: Int = 4
    private lateinit var calculatedValue: TextView
    private lateinit var formulaInputScrollView: HorizontalScrollView
    private lateinit var formulaInput: TextView
    private lateinit var adapter: ActionAdapter
    private lateinit var recyclerView: RecyclerView


    //TODO: Czy to potrzebne wciąż?
    override fun onConfigurationChanged(newConfig: Configuration) {
        super.onConfigurationChanged(newConfig)
        setLayoutManager()
        adaptButtons()
    }

    override fun onSaveInstanceState(outState: Bundle) {
        super.onSaveInstanceState(outState)
        outState.putInt("result", this.result)
        outState.putIntArray("stack", stack.value?.toIntArray() ?: IntArray(0))
    }

    override fun onRestoreInstanceState(savedInstanceState: Bundle) {
        super.onRestoreInstanceState(savedInstanceState)
        this.result = savedInstanceState.getInt("result", 0)
        val savedStack = savedInstanceState.getIntArray("stack")?.toMutableList() ?: mutableListOf()
        stack.value = savedStack
        displayResult()
        displayUpdatedFormula(stack.value ?: mutableListOf())
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        this.calculatedValue = findViewById<TextView>(R.id.calculatedValue)
        this.formulaInput = findViewById<TextView>(R.id.formulaInput)
        this.recyclerView = findViewById(R.id.recyclerView)
        this.formulaInputScrollView = findViewById<HorizontalScrollView>(R.id.formulaInputScrollView)
        recyclerView.layoutManager = GridLayoutManager(this, rowsNum)

        adaptButtons()

        recyclerView.adapter = this.adapter
        setLayoutManager()

        stack.observe(this, Observer {
            newStack ->
            displayUpdatedFormula(newStack)
        })
    }

    private fun initVerticalButtons():List<ButtonAction> {
        //Order is Crucial
        return listOf(
            ButtonAction.Number(1),
            ButtonAction.Number(2),
            ButtonAction.Number(3),
            ButtonAction.Function("") { },
            ButtonAction.Number(4),
            ButtonAction.Number(5),
            ButtonAction.Number(6),
            ButtonAction.Function("") { },
            ButtonAction.Number(7),
            ButtonAction.Number(8),
            ButtonAction.Number(9),
            ButtonAction.Function("") { },
            ButtonAction.Function("+") { add() },
            ButtonAction.Number(0),
            ButtonAction.Function("-") { subtract() },
            ButtonAction.Function("=") {
                calculateResult()
                displayResult()
            }
        )
    }
    private fun initHorizontalButtons():List<ButtonAction> {
        //Order is Crucial
        return listOf(
            ButtonAction.Number(1),
            ButtonAction.Number(2),
            ButtonAction.Number(3),
//            ButtonAction.Function("") { },
            ButtonAction.Number(4),
            ButtonAction.Number(5),
            ButtonAction.Number(6),
//            ButtonAction.Function("") { },
            ButtonAction.Number(7),
            ButtonAction.Number(8),
            ButtonAction.Number(9),
//            ButtonAction.Function("") { },
            ButtonAction.Function("+") { add() },
            ButtonAction.Number(0),
            ButtonAction.Function("-") { subtract() },
            ButtonAction.Function("=") {
                calculateResult()
                displayResult()
            }
        )
    }

    private fun pushToStack(value: Int) {
        val currentStack = this.stack.value ?: mutableListOf()
        currentStack.add(value)
        stack.value = currentStack
    }

    private fun popFromStack(): Int? {
        val currentStack = this.stack.value ?: mutableListOf()
        return if (currentStack.isNotEmpty()) {
            val value = currentStack.removeAt(currentStack.lastIndex)
            stack.value = currentStack
            value
        } else {
            null
        }
    }

    private fun adaptButtons() {
        val orientation = resources.configuration.orientation

        val buttonActions = if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
            initHorizontalButtons()
        } else {
            initVerticalButtons()
        }

        this.adapter = ActionAdapter(
            buttonActions,
            onNumberClick = { value ->
                pushToStack(value)
                println("Stack after adding $value: $stack")
            },
            onFunctionClick = { operation ->
                operation()
                println("Stack after operation: $stack")
            }
        )
    }

    private fun add() {
        val b = popFromStack()
        val a = popFromStack()
        if (a != null && b != null) {
           pushToStack(a + b)
        } else {
            println("Not enough operands to perform addition.")
        }
    }

    private fun subtract() {
        val b = popFromStack()
        val a = popFromStack()
        if (a != null && b != null) {
            pushToStack(a - b)
        } else {
            println("Not enough operands to perform subtraction.")
        }
    }

    private fun calculateResult() {
        val result = stack.value?.lastOrNull() ?: 0
        println("calculated result is: $result")
        this.result = result
    }

    private fun displayResult() {
        this.calculatedValue.text = getString(R.string.result, result)
    }

    private fun displayUpdatedFormula(newStack: MutableList<Int>) {
        this.formulaInput.text = newStack.toString()

        // Scroll to the end of the HorizontalScrollView
        formulaInputScrollView.post {
            formulaInputScrollView.fullScroll(View.FOCUS_RIGHT)
        }
    }

    private fun setLayoutManager() {
        val orientation = resources.configuration.orientation
        val spanCount = if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
            6
        } else {
            4
        }
        recyclerView.layoutManager = GridLayoutManager(this, spanCount)
    }

}