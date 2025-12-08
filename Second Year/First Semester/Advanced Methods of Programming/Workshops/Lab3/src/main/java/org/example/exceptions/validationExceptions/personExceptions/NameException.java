package org.example.exceptions.validationExceptions.personExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class NameException extends ValidationException {
    public NameException(String message) {
        super(message);
    }
}
