package lol.dutchu.mycalc

class Parser(private val tokens: List<String>) {
    private var pos = 0

    fun parseExpression(): Double {
        var result = parseTerm()
        while (pos < tokens.size) {
            val operator = tokens[pos]
            if (operator == "+" || operator == "-") {
                pos++
                val right = parseTerm()
                result = if (operator == "+") result + right else result - right
            } else {
                break
            }
        }
        return result
    }

    private fun parseTerm(): Double {
        var result = parseFactor()
        while (pos < tokens.size) {
            val operator = tokens[pos]
            if (operator == "*" || operator == "/") {
                pos++
                val right = parseFactor()
                result = if (operator == "*") result * right else result / right
            } else {
                break
            }
        }
        return result
    }

    private fun parseFactor(): Double {
        val token = tokens[pos]
        return if (token == "(") {
            pos++
            val result = parseExpression()
            if (tokens[pos] != ")") {
                throw IllegalArgumentException("Expected ')'")
            }
            pos++
            result
        } else {
            pos++
            token.toDoubleOrNull() ?: throw IllegalArgumentException("Expected number, got '$token'")
        }
    }
}

fun tokenize(expression: String): List<String> {
    val tokens = mutableListOf<String>()
    var i = 0
    while (i < expression.length) {
        val c = expression[i]
        when {
            c.isWhitespace() -> i++
            c.isDigit() || c == '.' -> {
                val sb = StringBuilder()
                while (i < expression.length && (expression[i].isDigit() || expression[i] == '.')) {
                    sb.append(expression[i])
                    i++
                }
                tokens.add(sb.toString())
            }
            c in "+-*/()" -> {
                tokens.add(c.toString())
                i++
            }
            else -> throw IllegalArgumentException("Invalid character: $c")
        }
    }
    return tokens
}

fun String.isNumber() = this.matches(Regex("\\d+(\\.\\d+)?"))
fun String.isOperator() = this.length == 1 && this[0] in "+-*/"
