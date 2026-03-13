package repository;

import java.util.List;
import java.util.Optional;

public interface Repository<ID, E> {
    Optional<E> save(E entity);

    void deleteById(ID id);

    E findById(ID id);

    List<E> findAll();
}
