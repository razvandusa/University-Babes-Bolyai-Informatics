package org.example.service;

import org.example.domain.Entity;
import org.example.repository.Repository;

/**
 * Abstract base class for service-layer implementations.
 * Provides common functionality for managing entities through a {@link Repository}
 * @param <ID> the type of the entity identifier
 * @param <E> the type of the entity
 */
public abstract class AbstractService<ID, E extends Entity<ID>> implements Service<ID, E> {
    /**
     * Repository used to store and retrieve entities
     */
    protected final Repository<ID, E> repository;

    /**
     * Creates an AbstractService with the given Repository
     *
     * @param repository the repository used by the service
     */
    public AbstractService(Repository<ID, E> repository) {
        this.repository = repository;
    }

    /**
     * Returns all entities managed by this service.
     *
     * @return an iterable containing all entities
     */
    @Override
    public Iterable<E> findAll() {
        return repository.findAll();
    }
}
