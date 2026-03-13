package service;

import domain.Airport;
import dto.AirportDTO;
import dto.AirportFilterDTO;

import java.util.List;
import java.util.Optional;

public interface IAirportService {
    Optional<Airport> createAirport(AirportDTO airportDTO);

    void deactivateAirport(int id);

    void updateAirport(int id, AirportDTO airportDTO);

    Airport getAirportById(int id);

    List<Airport> getAllAirports();

    List<Airport> getAllAirports(AirportFilterDTO filterDTO);
}