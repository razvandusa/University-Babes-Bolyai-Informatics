package org.example.exceptions.validationExceptions.userExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class UserTypeValidationException extends ValidationException {
    public UserTypeValidationException(String message) {
        super(message);
    }
}
