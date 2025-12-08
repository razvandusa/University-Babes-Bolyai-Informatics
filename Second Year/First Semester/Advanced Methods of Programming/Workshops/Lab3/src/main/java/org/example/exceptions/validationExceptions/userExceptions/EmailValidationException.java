package org.example.exceptions.validationExceptions.userExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class EmailValidationException extends ValidationException {
    public EmailValidationException(String message) {
        super(message);
    }
}
