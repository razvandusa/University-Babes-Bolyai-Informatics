package org.example.exceptions.validationExceptions.userExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class IdValidationException extends ValidationException {
    public IdValidationException(String message) {
        super(message);
    }
}
