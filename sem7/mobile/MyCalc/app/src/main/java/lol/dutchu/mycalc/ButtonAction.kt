package lol.dutchu.mycalc

sealed class ButtonAction {
    data class Number(val value: Int) : ButtonAction()
    data class Function(val label: String, val operation: () -> Unit) : ButtonAction()
}