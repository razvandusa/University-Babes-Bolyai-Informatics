package org.example.validation;

/**
 * Interface for validating entities.
 * Implementations should check that the provided entity satisfies business rules.
 *
 * @param <E> the type of entity to be validated
 */
public interface ValidationStrategy<E> {
    /**
     * Validates the given entity.
     * @param entity the entity to validate
     * @throws RuntimeException if the entity is invalid
     */
    void validate(E entity);
}