package org.example.exceptions.validationExceptions.friendshipExceptions;

import org.example.exceptions.validationExceptions.ValidationException;

public class SameIdException extends ValidationException {
    public SameIdException(String message) {
        super(message);
    }
}
