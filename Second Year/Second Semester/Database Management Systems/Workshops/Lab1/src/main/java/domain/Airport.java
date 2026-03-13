package domain;

public class Airport {
    private Integer airportID;
    private String name;
    private String city;
    private String country;

    public Airport(String name, String city, String country) {
        this.name = name;
        this.city = city;
        this.country = country;
    }

    public Airport(Integer airportID, String name, String city, String country) {
        this.airportID = airportID;
        this.name = name;
        this.city = city;
        this.country = country;
    }

    public Integer getId() {
        return airportID;
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

    public void setId(Integer airportID) {
        this.airportID = airportID;
    }
}
