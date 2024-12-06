package lol.dutchu.mycalc

import android.content.res.Configuration
import android.os.Bundle
import android.view.View
import android.widget.HorizontalScrollView
import android.widget.TextView
import androidx.activity.ComponentActivity
import androidx.activity.viewModels
import androidx.lifecycle.Observer
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlin.Int
import kotlin.collections.joinToString
import kotlin.math.floor

class MainActivity : ComponentActivity() {
    private val viewModel: CalculatorViewModel by viewModels()
    private val rowsNum: Int = 4
    private lateinit var calculatedValue: TextView
    private lateinit var formulaInputScrollView: HorizontalScrollView
    private lateinit var formulaInput: TextView
    private lateinit var adapter: ActionAdapter
    private lateinit var recyclerView: RecyclerView

    override fun onConfigurationChanged(newConfig: Configuration) {
        super.onConfigurationChanged(newConfig)
        setLayoutManager()
        adaptButtons()
        recyclerView.adapter = this.adapter
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        this.calculatedValue = findViewById<TextView>(R.id.calculatedValue)
        this.formulaInput = findViewById<TextView>(R.id.formulaInput)
        this.recyclerView = findViewById(R.id.recyclerView)
        this.formulaInputScrollView = findViewById<HorizontalScrollView>(R.id.formulaInputScrollView)
        recyclerView.layoutManager = GridLayoutManager(this, rowsNum)

        this.adapter = adaptButtons()

        recyclerView.adapter = this.adapter
        setLayoutManager()

        viewModel.expressionStack.observe(this, Observer { newStack ->
            displayUpdatedFormula(newStack)

        })

        viewModel.result.observe(this, Observer {
            result ->
            displayResult(result)
        })
    }

    private fun initVerticalButtons():List<ButtonAction> {
        //Order is Crucial
        return listOf(
            ButtonAction.Symbol(Buttons.ONE.label, Buttons.ONE.ordinal),
            ButtonAction.Symbol(Buttons.TWO.label, Buttons.TWO.ordinal),
            ButtonAction.Symbol(Buttons.THREE.label, Buttons.THREE.ordinal),
            ButtonAction.Function(Buttons.CLEAR, Buttons.CLEAR.ordinal),
            ButtonAction.Symbol(Buttons.FOUR.label, Buttons.FOUR.ordinal),
            ButtonAction.Symbol(Buttons.FIVE.label, Buttons.FOUR.ordinal),
            ButtonAction.Symbol(Buttons.SIX.label, Buttons.SIX.ordinal),
            ButtonAction.Symbol(Buttons.PARENTHESIS_LEFT.label, Buttons.PARENTHESIS_LEFT.ordinal),
            ButtonAction.Symbol(Buttons.SEVEN.label, Buttons.SEVEN.ordinal),
            ButtonAction.Symbol(Buttons.EIGHT.label, Buttons.EIGHT.ordinal),
            ButtonAction.Symbol(Buttons.NINE.label, Buttons.NINE.ordinal),
            ButtonAction.Symbol(Buttons.PARENTHESIS_RIGHT.label, Buttons.PARENTHESIS_RIGHT.ordinal),
            ButtonAction.Symbol(Buttons.ADD.label, Buttons.ADD.ordinal),
            ButtonAction.Symbol(Buttons.ZERO.label, Buttons.ZERO.ordinal),
            ButtonAction.Symbol(Buttons.SUBTRACT.label, Buttons.SUBTRACT.ordinal),
            ButtonAction.Function(Buttons.EVALUATE, Buttons.EVALUATE.ordinal),
            ButtonAction.Symbol(Buttons.MULTIPLY.label, Buttons.MULTIPLY.ordinal),
            ButtonAction.Symbol(Buttons.DIVIDE.label, Buttons.DIVIDE.ordinal),
            ButtonAction.Symbol(Buttons.DOT.label, Buttons.DOT.ordinal),
        )
    }
    private fun initHorizontalButtons():List<ButtonAction> {
        //Order is Crucial
        return listOf(
            ButtonAction.Symbol(Buttons.ONE.label, Buttons.ONE.ordinal),
            ButtonAction.Symbol(Buttons.TWO.label, Buttons.TWO.ordinal),
            ButtonAction.Symbol(Buttons.THREE.label, Buttons.THREE.ordinal),
            ButtonAction.Function(Buttons.CLEAR, Buttons.CLEAR.ordinal),
            ButtonAction.Symbol(Buttons.FOUR.label, Buttons.FOUR.ordinal),
            ButtonAction.Symbol(Buttons.FIVE.label, Buttons.FOUR.ordinal),
            ButtonAction.Symbol(Buttons.SIX.label, Buttons.SIX.ordinal),
            ButtonAction.Symbol(Buttons.PARENTHESIS_LEFT.label, Buttons.PARENTHESIS_LEFT.ordinal),
            ButtonAction.Symbol(Buttons.SEVEN.label, Buttons.SEVEN.ordinal),
            ButtonAction.Symbol(Buttons.EIGHT.label, Buttons.EIGHT.ordinal),
            ButtonAction.Symbol(Buttons.NINE.label, Buttons.NINE.ordinal),
            ButtonAction.Symbol(Buttons.PARENTHESIS_RIGHT.label, Buttons.PARENTHESIS_RIGHT.ordinal),
            ButtonAction.Symbol(Buttons.ADD.label, Buttons.ADD.ordinal),
            ButtonAction.Symbol(Buttons.ZERO.label, Buttons.ZERO.ordinal),
            ButtonAction.Symbol(Buttons.SUBTRACT.label, Buttons.SUBTRACT.ordinal),
            ButtonAction.Function(Buttons.EVALUATE, Buttons.EVALUATE.ordinal)
        )
    }

    private fun adaptButtons() : ActionAdapter {
        val orientation = resources.configuration.orientation
        val buttonActions = if (orientation == Configuration.ORIENTATION_LANDSCAPE) {
            initHorizontalButtons()
        } else {
            initVerticalButtons()
        }

        return ActionAdapter(
            buttonActions,
            onSymbolClick = { symbol ->
                viewModel.insertSymbol(symbol.label)
            },
            onFunctionClick = { button ->
                when (button) {
                    ButtonAction.Function(Buttons.EVALUATE, Buttons.EVALUATE.ordinal) -> viewModel.evaluateExpression()
                    ButtonAction.Function(Buttons.CLEAR, Buttons.CLEAR.ordinal) -> viewModel.clearExpression()
                    else -> println("Unknown function: $button")
                }
            },
            onEmptyClick = {
                //TODO: Lol
            }
        )
    }

    private fun displayResult(value: Double) {
        //TODO: Animate Result Display
        if (value == floor(value)) {
            this.calculatedValue.text = getString(R.string.result_int, value.toInt())
        } else {
            this.calculatedValue.text = getString(R.string.result_double, value)
        }
    }

    private fun displayUpdatedFormula(newStack: List<String>) {
        this.formulaInput.text = newStack.joinToString(" ")

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