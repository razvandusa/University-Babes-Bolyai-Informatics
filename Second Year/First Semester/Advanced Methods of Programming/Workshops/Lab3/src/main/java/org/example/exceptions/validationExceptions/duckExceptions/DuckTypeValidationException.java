package org.example.exceptions.validationExceptions.duckExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class DuckTypeValidationException extends ValidationException {
    public DuckTypeValidationException(String message) {
        super(message);
    }
}
