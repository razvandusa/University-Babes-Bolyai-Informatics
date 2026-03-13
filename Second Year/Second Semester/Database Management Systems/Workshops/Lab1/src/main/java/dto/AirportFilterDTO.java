package dto;

public class AirportFilterDTO {
    private String name;
    private String city;
    private String country;

    public AirportFilterDTO() {
    }

    public AirportFilterDTO(String name, String city, String country) {
        this.name = name;
        this.city = city;
        this.country = country;
    }

    public String getName() {
        return name;
    }

    public String getCity() {
        return city;
    }

    public String getCountry() {
        return country;
    }
}
