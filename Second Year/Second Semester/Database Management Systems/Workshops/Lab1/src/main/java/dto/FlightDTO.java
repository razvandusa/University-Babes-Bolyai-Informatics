package dto;

import java.time.LocalDateTime;

public class FlightDTO {
    private Integer airplaneID;
    private Integer departureAirportID;
    private Integer arrivalAirportID;
    private LocalDateTime departureDateTime;
    private LocalDateTime arrivalDateTime;

    public FlightDTO(Integer airplaneID, Integer departureAirportID, Integer arrivalAirportID, LocalDateTime departureDateTime, LocalDateTime arrivalDateTime) {
        this.airplaneID = airplaneID;
        this.departureAirportID = departureAirportID;
        this.arrivalAirportID = arrivalAirportID;
        this.departureDateTime = departureDateTime;
        this.arrivalDateTime = arrivalDateTime;
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

    public void setAirplaneID(Integer airplaneID) {
        this.airplaneID = airplaneID;
    }

    public void setDepartureAirportID(Integer departureAirportID) {
        this.departureAirportID = departureAirportID;
    }

    public void setArrivalAirportID(Integer arrivalAirportID) {
        this.arrivalAirportID = arrivalAirportID;
    }
}
