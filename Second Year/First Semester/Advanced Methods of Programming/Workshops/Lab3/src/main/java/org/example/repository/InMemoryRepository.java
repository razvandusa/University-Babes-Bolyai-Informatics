package org.example.repository;

import org.example.domain.Entity;

import java.util.HashMap;
import java.util.Map;

/**
 * Abstract in-memory repository for storing entities in a HashMap.
 * Provides basic CRUD operations: add, remove, findById, and findAll.
 *
 * @param <ID> the type of the entity identifier
 * @param <E>  the type of the entity, must extend {@code Entity<ID>}
 */
public abstract class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
    Map<ID, E> storage;

    /**
     * Constructs a new in-memory repository with an empty storage map.
     */
    public InMemoryRepository() {
        storage = new HashMap<>();
    }

    /**
     * Adds a new entity to the repository.
     *
     * @param entity the entity to add
     */
    @Override
    public void add(E entity) {
        storage.put(entity.getId(), entity);
    }

    /**
     * Removes an entity from the repository.
     *
     * @param entity the entity to remove
     */
    @Override
    public void remove(E entity) {
        storage.remove(entity.getId());
    }

    /**
     * Finds an entity by its ID.
     *
     * @param id the ID of the entity to find
     * @return the entity with the given ID, or null if not found
     */
    @Override
    public E findById(ID id) {
        return storage.get(id);
    }

    /**
     * Returns all entities stored in the repository.
     *
     * @return an iterable collection of all entities
     */
    @Override
    public Iterable<E> findAll() {
        return storage.values();
    }
}
