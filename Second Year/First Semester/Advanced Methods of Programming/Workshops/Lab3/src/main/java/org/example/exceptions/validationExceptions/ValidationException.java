package org.example.exceptions.validationExceptions;

/**
 * Exception thrown when validation fails.
 */
public class ValidationException extends RuntimeException {
    public ValidationException(String message) {
        super(message);
    }
}
