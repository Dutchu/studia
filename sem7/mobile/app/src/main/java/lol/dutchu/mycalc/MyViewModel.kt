package lol.dutchu.mycalc

import androidx.lifecycle.ViewModel

class MyViewModel : ViewModel() {

    private var counter: Int
        get() {
            return counter
        }
        set(value) {
            counter = value
        }

    fun increment() {
        counter++
    }
}