package org.example;

public class WrongValuesPeselException extends IllegalArgumentException {
    public WrongValuesPeselException(String message) {
        super(message);
    }
}
