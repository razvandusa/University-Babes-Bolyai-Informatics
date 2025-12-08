package org.example.service;

import org.example.domain.Entity;

/**
 * Generic service interface that defines the basic business operations
 * for managing entities.
 *
 * @param <ID> the type of the entity identifier
 * @param <E>  the type of the entity managed by this service
 */
public interface Service<ID, E extends Entity<ID>> {

    /**
     * Adds a new entity using the provided fields.
     *
     * @param fields a variable number of strings representing the entity data
     */
    void add(String ... fields);

    /**
     * Removes the entity with the given identifier
     * @param id the identifier of the entity to be removed
     */
    void remove(String id);

    /**
     * Generated and returns a new unique identifier
     *
     * @return a newly generated unique identifier
     */
    ID generateID();

    /**
     * Retrieves all entities managed by this service.
     *
     * @return an {@link Iterable} containing all entities
     */
    Iterable<E> findAll();
}
