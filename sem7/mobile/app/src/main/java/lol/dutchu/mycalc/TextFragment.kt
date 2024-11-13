package lol.dutchu.mycalc

import android.R.attr.content
import android.R.id.content
import androidx.fragment.app.Fragment
import android.os.Bundle
import android.view.LayoutInflater
import android.view.ViewGroup


class TextFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ) = content {
        // Write your @Composable content here
        val viewModel: ExampleViewModel = viewModel()

        // or extract it into a separate, testable method
        ExampleComposable(viewModel)
    }
}