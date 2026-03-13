package dto;

public class AirplaneFilterDTO {
    private String model;
    private Integer capacity;

    public AirplaneFilterDTO() {
    }

    public AirplaneFilterDTO(String model, Integer capacity) {
        this.model = model;
        this.capacity = capacity;
    }

    public String getModel() {
        return model;
    }

    public Integer getCapacity() {
        return capacity;
    }
}
