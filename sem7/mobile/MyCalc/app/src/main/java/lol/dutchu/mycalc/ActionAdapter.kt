package lol.dutchu.mycalc

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.RecyclerView

class ActionAdapter(
    private var buttonActions: List<ButtonAction>,
    private val onSymbolClick: (ButtonAction.Symbol) -> Unit,
    private val onFunctionClick: (ButtonAction.Function) -> Unit,
    private val onEmptyClick: () -> Unit
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
        holder.bind(action)
    }

    override fun getItemCount(): Int = buttonActions.size

    fun updateButtonActions(newActions: List<ButtonAction>) {
        val diffCallback = ButtonActionDiffCallback(this.buttonActions, newActions)
        val diffResult = DiffUtil.calculateDiff(diffCallback)
        this.buttonActions = newActions
        diffResult.dispatchUpdatesTo(this)
    }

    inner class ActionButtonViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        private val actionButton: Button = view.findViewById(R.id.actionButton)

        fun bind(action: ButtonAction) {
            when (action) {
                is ButtonAction.Symbol -> {
                    actionButton.text = action.label
                    actionButton.setOnClickListener { onSymbolClick(action) }
                }
                is ButtonAction.Function -> {
                    actionButton.text = action.button.label
                    actionButton.setOnClickListener { onFunctionClick(action) }
                }
                is ButtonAction.Empty -> {
                    actionButton.text = ""
                    actionButton.setOnClickListener { onEmptyClick() }
                }
            }
        }
    }

    class ButtonActionDiffCallback(
        private val oldList: List<ButtonAction>,
        private val newList: List<ButtonAction>
    ) : DiffUtil.Callback() {
        override fun getOldListSize(): Int = oldList.size

        override fun getNewListSize(): Int = newList.size

        override fun areItemsTheSame(oldItemPosition: Int, newItemPosition: Int): Boolean {
            val oldItem = oldList[oldItemPosition]
            val newItem = newList[newItemPosition]

            return when {
                oldItem is ButtonAction.Symbol && newItem is ButtonAction.Symbol -> oldItem.id == newItem.id
                oldItem is ButtonAction.Function && newItem is ButtonAction.Function -> oldItem.id == newItem.id
                oldItem is ButtonAction.Empty && newItem is ButtonAction.Empty -> true
                else -> false
            }
        }
        override fun areContentsTheSame(oldItemPosition: Int, newItemPosition: Int): Boolean {
            return oldList[oldItemPosition] == newList[newItemPosition]
        }
    }
}