package dto;

public class AirplaneDTO {
    private String model;
    private int capacity;

    public AirplaneDTO(String model, int capacity) {
        this.model = model;
        this.capacity = capacity;
    }

    public String getModel() {
        return model;
    }

    public int getCapacity() {
        return capacity;
    }
}
