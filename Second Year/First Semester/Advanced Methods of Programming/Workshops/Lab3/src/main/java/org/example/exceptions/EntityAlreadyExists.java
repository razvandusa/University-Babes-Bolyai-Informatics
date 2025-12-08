package org.example.exceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class EntityAlreadyExists extends ValidationException {
    public EntityAlreadyExists(String message) {
        super(message);
    }
}
