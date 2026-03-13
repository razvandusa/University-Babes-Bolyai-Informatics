package service;

import domain.Airplane;
import dto.AirplaneDTO;
import dto.AirplaneFilterDTO;

import java.util.List;
import java.util.Optional;

public interface IAirplaneService {
    Optional<Airplane> createAirplane(AirplaneDTO airplaneDTO);

    void deactivateAirplane(int id);

    void updateAirplane(int id, AirplaneDTO airplaneDTO);

    Airplane getAirplaneById(int id);

    List<Airplane> getAllAirplanes();

    List<Airplane> getAllAirplanes(AirplaneFilterDTO filterDTO);
}