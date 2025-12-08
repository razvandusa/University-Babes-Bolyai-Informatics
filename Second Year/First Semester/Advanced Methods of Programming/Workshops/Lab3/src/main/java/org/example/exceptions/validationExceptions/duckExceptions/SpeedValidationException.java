package org.example.exceptions.validationExceptions.duckExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class SpeedValidationException extends ValidationException {
    public SpeedValidationException(String message) {
        super(message);
    }
}
