package org.example.exceptions.validationExceptions.userExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class UsernameValidationException extends ValidationException {
    public UsernameValidationException(String message) { super(message); }
}
