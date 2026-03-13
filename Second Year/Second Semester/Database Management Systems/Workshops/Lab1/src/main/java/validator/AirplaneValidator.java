package validator;

import dto.AirplaneDTO;

public class AirplaneValidator implements Validator<AirplaneDTO>{
    @Override
    public void validate(AirplaneDTO airplaneDTO) {
        if (!validateModel(airplaneDTO.getModel())) {
            throw new IllegalArgumentException("Model cannot be empty");
        }
        if (!validateCapacity(airplaneDTO.getCapacity())) {
            throw new IllegalArgumentException("Capacity must be greater than 0");
        }
    }

    private boolean validateModel(String model) {
        return model != null && !model.trim().isEmpty();
    }

    private boolean validateCapacity(int capacity) {
        return capacity > 0;
    }
}
