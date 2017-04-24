package fr.licinfo;

/**
 * Created by Alexis Couvreur on 24/04/2017.
 */
public class InvalidSentenceException extends Exception {
    public InvalidSentenceException() {
        super();
    }

    public InvalidSentenceException(String message) {
        super(message);
    }

    public InvalidSentenceException(String message, Throwable cause) {
        super(message, cause);
    }

    public InvalidSentenceException(Throwable cause) {
        super(cause);
    }
}
