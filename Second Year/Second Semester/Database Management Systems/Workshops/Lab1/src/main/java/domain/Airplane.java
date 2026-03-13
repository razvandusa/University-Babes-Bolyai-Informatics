package domain;

public class Airplane {
    private Integer airplaneID;
    private String model;
    private Integer capacity;

    public Airplane(String model, Integer capacity) {
        this.model = model;
        this.capacity = capacity;
    }

    public Airplane(Integer airplaneID, String model, Integer capacity) {
        this.airplaneID = airplaneID;
        this.model = model;
        this.capacity = capacity;
    }

    public Integer getId() {
        return airplaneID;
    }

    public String getModel() {
        return model;
    }

    public Integer getCapacity() {
        return capacity;
    }

    public void setId(Integer airplaneID) {
        this.airplaneID = airplaneID;
    }
}
