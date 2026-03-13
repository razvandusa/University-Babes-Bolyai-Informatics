package repository;

import domain.Airplane;

public interface IAirplaneRepository extends Repository<Integer, Airplane> {
    void update(Airplane airplane);
}
