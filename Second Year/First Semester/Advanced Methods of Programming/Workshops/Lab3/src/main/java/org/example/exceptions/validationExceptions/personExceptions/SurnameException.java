package org.example.exceptions.validationExceptions.personExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class SurnameException extends ValidationException {
    public SurnameException(String message) {
        super(message);
    }
}
