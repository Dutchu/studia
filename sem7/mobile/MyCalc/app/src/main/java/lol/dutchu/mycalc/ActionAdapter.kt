package lol.dutchu.mycalc

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.recyclerview.widget.RecyclerView
import java.util.Locale

class ActionAdapter(
    private val buttonActions: List<ButtonAction>,
    private val onNumberClick: (Int) -> Unit,
    private val onFunctionClick: (() -> Unit) -> Unit
    ) : RecyclerView.Adapter<ActionAdapter.ActionButtonViewHolder>() {

    override fun onCreateViewHolder(
        parent: ViewGroup,
        viewType: Int
    ): ActionButtonViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.keyboard_button, parent, false)
        return ActionButtonViewHolder(view)
    }

    override fun onBindViewHolder(holder: ActionButtonViewHolder, position: Int) {

        val action = buttonActions[position]
        when (action) {
            is ButtonAction.Number -> {
                holder.actionButton.text = String.format(Locale.US, "%d", action.value)
                holder.actionButton.setOnClickListener { onNumberClick(action.value) }
            }
            is ButtonAction.Function -> {
                holder.actionButton.text = action.label
                holder.actionButton.setOnClickListener { onFunctionClick(action.operation) }
            }
        }
    }

    override fun getItemCount(): Int = buttonActions.size

    class ActionButtonViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val actionButton: Button = view.findViewById(R.id.actionButton)
    }

}