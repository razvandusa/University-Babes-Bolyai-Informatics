package validator;

import dto.AirportDTO;

public class AirportValidator implements Validator<AirportDTO>{
    @Override
    public void validate(AirportDTO airportDTO) {
        if (!validateName(airportDTO.getName())) {
            throw new IllegalArgumentException("Name cannot be empty");
        }
        if (!validateCity(airportDTO.getCity())) {
            throw new IllegalArgumentException("City cannot be empty");
        }
        if (!validateCountry(airportDTO.getCountry())) {
            throw new IllegalArgumentException("Country cannot be empty");
        }
    }

    private boolean validateName(String name) {
        return name != null && !name.trim().isEmpty();
    }

    private boolean validateCity(String city) {
        return city != null && !city.trim().isEmpty();
    }

    private boolean validateCountry(String country) {
        return country != null && !country.trim().isEmpty();
    }
}
