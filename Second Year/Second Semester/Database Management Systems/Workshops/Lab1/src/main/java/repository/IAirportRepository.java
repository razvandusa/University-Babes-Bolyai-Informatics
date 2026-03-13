package repository;

import domain.Airport;

public interface IAirportRepository extends Repository<Integer, Airport> {
    void update(Airport airport);
}
