package service;

import domain.Flight;
import dto.FlightDTO;
import dto.FlightFilterDTO;
import repository.IFlightRepository;
import validator.Validator;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class FlightServiceImpl implements IFlightService {
    private final IFlightRepository flightRepository;
    private final Validator<FlightDTO> flightValidator;
    private final Validator<Integer> idValidator;

    public FlightServiceImpl(IFlightRepository flightRepository, Validator<FlightDTO> flightValidator, Validator<Integer> idValidator) {
        this.flightRepository = flightRepository;
        this.flightValidator = flightValidator;
        this.idValidator = idValidator;
    }


    @Override
    public Optional<Flight> createFlight(FlightDTO flightDTO) {
        flightValidator.validate(flightDTO);
        return flightRepository.save(new Flight(flightDTO.getAirplaneID(), flightDTO.getDepartureAirportID(), flightDTO.getArrivalAirportID(), flightDTO.getDepartureDateTime(), flightDTO.getArrivalDateTime()));
    }

    @Override
    public void deactivateFlight(int id) {
        idValidator.validate(id);
        flightRepository.deleteById(id);
    }

    @Override
    public void updateFlight(int id, FlightDTO flightDTO) {
        idValidator.validate(id);
        flightValidator.validate(flightDTO);
        flightRepository.update(new Flight(id, flightDTO.getAirplaneID(), flightDTO.getDepartureAirportID(), flightDTO.getArrivalAirportID(), flightDTO.getDepartureDateTime(), flightDTO.getArrivalDateTime()));
    }

    @Override
    public Flight getFlightById(int id) {
        idValidator.validate(id);
        return flightRepository.findById(id);
    }

    @Override
    public List<Flight> getAllFlights() {
        return flightRepository.findAll();
    }

    @Override
    public List<Flight> getAllFlights(FlightFilterDTO filterDTO) {
        List<Flight> flights = new ArrayList<>();
        for (Flight flight : flightRepository.findAll()) {
            if ((filterDTO.getAirplaneID() == null || Objects.equals(flight.getAirplaneID(), filterDTO.getAirplaneID())) &&
                    (filterDTO.getDepartureAirportID() == null || Objects.equals(flight.getDepartureAirportID(), filterDTO.getDepartureAirportID())) &&
                    (filterDTO.getArrivalAirportID() == null || Objects.equals(flight.getArrivalAirportID(), filterDTO.getArrivalAirportID())) &&
                    (filterDTO.getDepartureDateTime() == null || Objects.equals(flight.getDepartureDateTime(), filterDTO.getDepartureDateTime())) &&
                    (filterDTO.getArrivalDateTime() == null || Objects.equals(flight.getArrivalDateTime(), filterDTO.getArrivalDateTime()))) {
                flights.add(flight);
            }
        }
        return flights;
    }
}
