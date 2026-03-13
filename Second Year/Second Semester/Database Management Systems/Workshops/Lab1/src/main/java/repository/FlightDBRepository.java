package repository;

import domain.Flight;
import utils.DatabaseManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class FlightDBRepository implements IFlightRepository {
    private final DatabaseManager databaseManager;

    public FlightDBRepository(Properties properties) {
        databaseManager = new DatabaseManager(properties);
    }

    public Optional<Flight> save(Flight flight) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO flights (AirplaneID, DepartureAirportID, ArrivalAirportID, DepartureDateTime, ArrivalDateTime) VALUES (?, ?, ?, ?, ?) RETURNING FlightID")) {
            preparedStatement.setInt(1, flight.getAirplaneID());
            preparedStatement.setInt(2, flight.getDepartureAirportID());
            preparedStatement.setInt(3, flight.getArrivalAirportID());
            preparedStatement.setTimestamp(4, Timestamp.valueOf(flight.getDepartureDateTime()));
            preparedStatement.setTimestamp(5, Timestamp.valueOf(flight.getArrivalDateTime()));
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int FlightID = resultSet.getInt("FlightID");
                return Optional.of(new Flight(FlightID, flight.getAirplaneID(), flight.getDepartureAirportID(), flight.getArrivalAirportID(), flight.getDepartureDateTime(), flight.getArrivalDateTime()));
            } else {
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error saving flight", e);
        }
    }

    @Override
    public void deleteById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM flights WHERE FlightID = ?")) {
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Flight findById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM flights WHERE FlightID = ?")) {
            preparedStatement.setInt(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int FlightID = resultSet.getInt("FlightID");
                int AirplaneID = resultSet.getInt("AirplaneID");
                int DepartureAirportID = resultSet.getInt("DepartureAirportID");
                int ArrivalAirportID = resultSet.getInt("ArrivalAirportID");
                LocalDateTime departureDateTime = resultSet.getTimestamp("DepartureDateTime").toLocalDateTime();
                LocalDateTime arrivalDateTime = resultSet.getTimestamp("ArrivalDateTime").toLocalDateTime();
                return new Flight(FlightID, AirplaneID, DepartureAirportID, ArrivalAirportID, departureDateTime, arrivalDateTime);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public List<Flight> findAll() {
        List<Flight> flights = new ArrayList<>();
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM flights")) {
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                int FlightID = resultSet.getInt("FlightID");
                int AirplaneID = resultSet.getInt("AirplaneID");
                int DepartureAirportID = resultSet.getInt("DepartureAirportID");
                int ArrivalAirportID = resultSet.getInt("ArrivalAirportID");
                LocalDateTime departureDateTime = resultSet.getTimestamp("DepartureDateTime").toLocalDateTime();
                LocalDateTime arrivalDateTime = resultSet.getTimestamp("ArrivalDateTime").toLocalDateTime();
                flights.add(new Flight(FlightID, AirplaneID, DepartureAirportID, ArrivalAirportID, departureDateTime, arrivalDateTime));
            }
            return flights;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return flights;
    }

    @Override
    public void update(Flight flight) {
        String sql = "UPDATE flights SET AirplaneID = ?, DepartureAirportID = ?, ArrivalAirportID = ?, DepartureDateTime = ?, ArrivalDateTime = ? WHERE FlightID = ?";
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, flight.getAirplaneID());
            preparedStatement.setInt(2, flight.getDepartureAirportID());
            preparedStatement.setInt(3, flight.getArrivalAirportID());
            preparedStatement.setTimestamp(4, Timestamp.valueOf(flight.getDepartureDateTime()));
            preparedStatement.setTimestamp(5, Timestamp.valueOf(flight.getArrivalDateTime()));
            preparedStatement.setInt(6, flight.getId());
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error updating flight", e);
        }
    }

}
