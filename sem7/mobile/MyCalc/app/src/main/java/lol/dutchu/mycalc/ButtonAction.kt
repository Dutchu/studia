package lol.dutchu.mycalc

sealed class ButtonAction {
    data class Symbol(val label: String, val id: Int) : ButtonAction()
    data class Function(val button: Buttons, val id: Int) : ButtonAction()
    object Empty : ButtonAction()
}