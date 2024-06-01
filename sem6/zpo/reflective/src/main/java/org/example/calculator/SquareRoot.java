package org.example.calculator;

public class SquareRoot  implements Operation {
    @Override
    public double calculate(double a, double b) {
        return Math.sqrt(a);
    }
}
