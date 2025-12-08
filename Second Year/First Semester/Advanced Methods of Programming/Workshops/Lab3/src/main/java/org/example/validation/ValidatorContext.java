package org.example.validation;

import org.example.exceptions.validationExceptions.ValidationException;

/**
 * Context for applying a validation strategy to entities.
 * Encapsulates a {@link ValidationStrategy} and delegates validation calls to it.
 *
 * @param <E> the type of entity to be validated
 */
public class ValidatorContext<E> {
    private ValidationStrategy<E> strategy;

    /**
     * Constructs a ValidatorContext with the specified validation strategy.
     *
     * @param validationStrategy the strategy to use for validation
     */
    public ValidatorContext(ValidationStrategy<E> validationStrategy) {
        this.strategy = validationStrategy;
    }

    /**
     * Sets a new validation strategy for this context.
     *
     * @param validationStrategy the new validation strategy to use
     */
    public void setStrategy(ValidationStrategy<E> validationStrategy) {
        this.strategy = validationStrategy;
    }

    /**
     * Validates the given entity using the current validation strategy.
     *
     * @param entity the entity to validate
     * @throws ValidationException if the entity is invalid according to the strategy
     */
    public void validate(E entity) throws ValidationException {
        strategy.validate(entity);
    }
}
