package service;

import domain.Airport;
import dto.AirportDTO;
import dto.AirportFilterDTO;
import repository.IAirportRepository;
import validator.Validator;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class AirportServiceImpl implements IAirportService {
    private final IAirportRepository airportRepository;
    private final Validator<AirportDTO> airportValidator;
    private final Validator<Integer> idValidator;

    public AirportServiceImpl(IAirportRepository airportRepository, Validator<AirportDTO> airportValidator, Validator<Integer> idValidator) {
        this.airportRepository = airportRepository;
        this.airportValidator = airportValidator;
        this.idValidator = idValidator;
    }

    @Override
    public Optional<Airport> createAirport(AirportDTO airportDTO) {
        airportValidator.validate(airportDTO);
        return airportRepository.save(new Airport(airportDTO.getName(), airportDTO.getCity(), airportDTO.getCountry()));
    }

    @Override
    public void deactivateAirport(int id) {
        idValidator.validate(id);
        airportRepository.deleteById(id);
    }

    @Override
    public void updateAirport(int id, AirportDTO airportDTO) {
        idValidator.validate(id);
        airportValidator.validate(airportDTO);
        airportRepository.update(new Airport(id, airportDTO.getName(), airportDTO.getCity(), airportDTO.getCountry()));
    }

    @Override
    public Airport getAirportById(int id) {
        idValidator.validate(id);
        return airportRepository.findById(id);
    }

    @Override
    public List<Airport> getAllAirports() {
        return airportRepository.findAll();
    }

    @Override
    public List<Airport> getAllAirports(AirportFilterDTO filterDTO) {
        List<Airport> airports = new ArrayList<>();
        for (Airport airport : airportRepository.findAll()) {
            if ((filterDTO.getName() == null || airport.getName().equals(filterDTO.getName())) &&
                    (filterDTO.getCity() == null || airport.getCity().equals(filterDTO.getCity())) &&
                    (filterDTO.getCountry() == null || airport.getCountry().equals(filterDTO.getCountry()))) {
                airports.add(airport);
            }
        }
        return airports;
    }
}
