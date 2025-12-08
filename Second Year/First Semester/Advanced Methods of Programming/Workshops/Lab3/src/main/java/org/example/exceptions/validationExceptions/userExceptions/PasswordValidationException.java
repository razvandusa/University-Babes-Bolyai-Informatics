package org.example.exceptions.validationExceptions.userExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class PasswordValidationException extends ValidationException {
    public PasswordValidationException(String message) {
        super(message);
    }
}
