package repository;

import domain.Flight;

public interface IFlightRepository extends Repository<Integer, Flight> {
    void update(Flight flight);
}