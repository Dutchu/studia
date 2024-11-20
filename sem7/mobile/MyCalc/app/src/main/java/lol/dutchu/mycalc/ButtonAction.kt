package lol.dutchu.mycalc

import android.view.View

data class Action (
    val label: String,
    val clickListener: View.OnClickListener
)