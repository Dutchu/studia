package org.example.calculator;

public class Multiplication implements Operation {
    @Override
    public double calculate(double a, double b) {
        return a * b;
    }
}
