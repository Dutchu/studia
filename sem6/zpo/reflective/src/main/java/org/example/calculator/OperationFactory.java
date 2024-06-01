package org.example.calculator;

public class OperationFactory {
    public static Operation getOperation(String operator) {
        switch (operator) {
            case "+":
                return new Addition();
            case "-":
                return new Subtraction();
            case "*":
                return new Multiplication();
            case "/":
                return new Division();
            case "^":
                return new SquareRoot();
            default:
                throw new IllegalArgumentException("Invalid operator");
        }
    }
}
