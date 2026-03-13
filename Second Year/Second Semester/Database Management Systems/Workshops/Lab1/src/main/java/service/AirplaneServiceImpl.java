package service;

import domain.Airplane;
import dto.AirplaneDTO;
import dto.AirplaneFilterDTO;
import repository.IAirplaneRepository;
import validator.Validator;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class AirplaneServiceImpl implements IAirplaneService {
    private final IAirplaneRepository airplaneRepository;
    private final Validator<AirplaneDTO> airplaneValidator;
    private final Validator<Integer> idValidator;

    public AirplaneServiceImpl(IAirplaneRepository airplaneRepository, Validator<AirplaneDTO> airplaneValidator, Validator<Integer> idValidator) {
        this.airplaneRepository = airplaneRepository;
        this.airplaneValidator = airplaneValidator;
        this.idValidator = idValidator;
    }

    @Override
    public Optional<Airplane> createAirplane(AirplaneDTO airplaneDTO) {
        airplaneValidator.validate(airplaneDTO);
        return airplaneRepository.save(new Airplane(airplaneDTO.getModel(), airplaneDTO.getCapacity()));
    }

    @Override
    public void deactivateAirplane(int id) {
        idValidator.validate(id);
        airplaneRepository.deleteById(id);
    }

    @Override
    public void updateAirplane(int id, AirplaneDTO airplaneDTO) {
        idValidator.validate(id);
        airplaneValidator.validate(airplaneDTO);
        airplaneRepository.update(new Airplane(id, airplaneDTO.getModel(), airplaneDTO.getCapacity()));
    }

    @Override
    public Airplane getAirplaneById(int id) {
        idValidator.validate(id);
        return airplaneRepository.findById(id);
    }

    @Override
    public List<Airplane> getAllAirplanes() {
        return airplaneRepository.findAll();
    }

    @Override
    public List<Airplane> getAllAirplanes(AirplaneFilterDTO filterDTO) {
        List<Airplane> airplanes = new ArrayList<>();
        for (Airplane airplane : airplaneRepository.findAll()) {
            if ((filterDTO.getModel() == null || Objects.equals(airplane.getModel(), filterDTO.getModel())) &&
                    (filterDTO.getCapacity() == null || Objects.equals(airplane.getCapacity(), filterDTO.getCapacity()))) {
                airplanes.add(airplane);
            }
        }
        return airplanes;
    }
}
