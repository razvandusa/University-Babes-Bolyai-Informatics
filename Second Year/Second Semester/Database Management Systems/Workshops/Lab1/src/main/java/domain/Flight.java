package domain;

import java.time.LocalDateTime;

public class Flight {
    private Integer flightID;
    private Integer airplaneID;
    private Integer departureAirportID;
    private Integer arrivalAirportID;
    private LocalDateTime departureDateTime;
    private LocalDateTime arrivalDateTime;

    public Flight(Integer airplaneID, Integer departureAirportID, Integer arrivalAirportID, LocalDateTime departureDateTime, LocalDateTime arrivalDateTime) {
        this.airplaneID = airplaneID;
        this.departureAirportID = departureAirportID;
        this.arrivalAirportID = arrivalAirportID;
        this.departureDateTime = departureDateTime;
        this.arrivalDateTime = arrivalDateTime;
    }

    public Flight(Integer flightID, Integer airplaneID, Integer departureAirportID, Integer arrivalAirportID, LocalDateTime departureDateTime, LocalDateTime arrivalDateTime) {
        this.flightID = flightID;
        this.airplaneID = airplaneID;
        this.departureAirportID = departureAirportID;
        this.arrivalAirportID = arrivalAirportID;
        this.departureDateTime = departureDateTime;
        this.arrivalDateTime = arrivalDateTime;
    }

    public Integer getId() {
        return flightID;
    }

    public Integer getAirplaneID() {
        return airplaneID;
    }

    public Integer getDepartureAirportID() {
        return departureAirportID;
    }

    public Integer getArrivalAirportID() {
        return arrivalAirportID;
    }

    public LocalDateTime getArrivalDateTime() {
        return arrivalDateTime;
    }

    public LocalDateTime getDepartureDateTime() {
        return departureDateTime;
    }

    public void setArrivalDateTime(LocalDateTime arrivalDateTime) {
        this.arrivalDateTime = arrivalDateTime;
    }

    public void setDepartureDateTime(LocalDateTime departureDateTime) {
        this.departureDateTime = departureDateTime;
    }

    public void setId(Integer flightID) {
        this.flightID = flightID;
    }
}