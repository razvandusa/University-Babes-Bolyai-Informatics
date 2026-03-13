package validator;

import dto.FlightDTO;

public class FlightValidator implements Validator<FlightDTO>{
    @Override
    public void validate(FlightDTO flightDTO) {
        if (!validateAirplane(flightDTO.getAirplaneID())) {
            throw new IllegalArgumentException("Invalid airplane ID");
        }
        if (!validateAirports(flightDTO.getDepartureAirportID(), flightDTO.getArrivalAirportID())) {
            throw new IllegalArgumentException("Invalid airport IDs");
        }
        if (!validateDates(flightDTO.getDepartureDateTime(), flightDTO.getArrivalDateTime())) {
            throw new IllegalArgumentException("Invalid dates");
        }
    }

    public boolean validateAirplane(int airplaneId) {
        return airplaneId > 0;
    }

    public boolean validateAirports(int departureAirportId, int arrivalAirportId) {
        return departureAirportId > 0 && arrivalAirportId > 0;
    }

    public boolean validateDates(java.time.LocalDateTime departureDateTime, java.time.LocalDateTime arrivalDateTime) {
        return departureDateTime != null && arrivalDateTime != null && departureDateTime.isBefore(arrivalDateTime);
    }
}
