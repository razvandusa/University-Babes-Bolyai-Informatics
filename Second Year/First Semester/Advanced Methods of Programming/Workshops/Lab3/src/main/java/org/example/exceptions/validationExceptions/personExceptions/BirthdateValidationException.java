package org.example.exceptions.validationExceptions.personExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class BirthdateValidationException extends ValidationException {
    public BirthdateValidationException(String message) {
        super(message);
    }
}
