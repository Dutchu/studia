package lol.dutchu.mycalc

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.SavedStateHandle
import androidx.lifecycle.ViewModel

class CalculatorViewModel(private val savedStateHandle: SavedStateHandle) : ViewModel() {
    companion object {
        private const val KEY_EXPRESSION_STACK = "expressionStack"
        private const val KEY_RESULT = "result"
    }

    private val _expressionStack = MutableLiveData<List<String>>(
        savedStateHandle.get<List<String>>(KEY_EXPRESSION_STACK) ?: emptyList()
    )
    val expressionStack: LiveData<List<String>> get() = _expressionStack

    private val _result = MutableLiveData<Double>(
        savedStateHandle.get<Double>(KEY_RESULT) ?: 0.0
    )
    val result: LiveData<Double> get() = _result


    fun setExpressionStack(newStack: List<String>) {
        _expressionStack.value = newStack
        savedStateHandle[KEY_EXPRESSION_STACK] = newStack
    }

    fun setResult(newResult: Double) {
        _result.value = newResult
        savedStateHandle[KEY_RESULT] = newResult
    }

    fun insertSymbol(symbol: String) {
        val updatedList = _expressionStack.value.orEmpty() + symbol
        setExpressionStack(updatedList)
    }

    fun clearExpression() {
        setExpressionStack(emptyList())
    }

    fun evaluateExpression() {
        val expressionStr = _expressionStack.value?.joinToString("") ?: ""
        try {
            val tokens = tokenize(expressionStr)
            val parser = Parser(tokens)
            val evaluatedResult = parser.parseExpression()
            setResult(evaluatedResult)
        } catch (e: Exception) {
            setResult(Double.NaN)
        }
    }

}