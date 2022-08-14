package expetions;

public class VectorDifferentLengthException extends RuntimeException {
    public VectorDifferentLengthException() {
        super();
    }

    public VectorDifferentLengthException(String message) {
        super(message);
    }

    public VectorDifferentLengthException(String message, Throwable cause) {
        super(message, cause);
    }

    public VectorDifferentLengthException(Throwable cause) {
        super(cause);
    }

    protected VectorDifferentLengthException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
        super(message, cause, enableSuppression, writableStackTrace);
    }
}
