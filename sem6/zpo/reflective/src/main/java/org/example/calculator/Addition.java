package org.example.calculator;

public class Addition implements Operation {
    @Override
    public double calculate(double a, double b) {
        return a + b;
    }
}
