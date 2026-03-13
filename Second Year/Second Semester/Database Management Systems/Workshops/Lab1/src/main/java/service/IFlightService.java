package service;

import domain.Flight;
import dto.FlightDTO;
import dto.FlightFilterDTO;

import java.util.List;
import java.util.Optional;

public interface IFlightService {
    Optional<Flight> createFlight(FlightDTO flightDTO);

    void deactivateFlight(int id);

    void updateFlight(int id, FlightDTO flightDTO);

    Flight getFlightById(int id);

    List<Flight> getAllFlights();

    List<Flight> getAllFlights(FlightFilterDTO filterDTO);
}