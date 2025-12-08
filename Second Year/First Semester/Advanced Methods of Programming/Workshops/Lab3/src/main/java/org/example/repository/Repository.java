package org.example.repository;

import org.example.domain.Entity;

/**
 * Generic repository interface for managing entities in a storage system.
 *
 * @param <ID> the type of the entity identifier
 * @param <E>  the type of the entity, must extend {@code Entity<ID>}
 */
public interface Repository<ID, E extends Entity<ID>> {

    /**
     * Adds a new entity to the repository.
     *
     * @param entity the entity to add
     */
    void add(E entity);

    /**
     * Removes an entity from the repository.
     *
     * @param entity the entity to remove
     */
    void remove(E entity);

    /**
     * Finds an entity by its identifier.
     *
     * @param id the identifier of the entity
     * @return the entity with the given ID, or null if not found
     */
    E findById(ID id);

    /**
     * Returns all entities stored in the repository.
     *
     * @return an iterable collection of all entities
     */
    Iterable<E> findAll();
}
