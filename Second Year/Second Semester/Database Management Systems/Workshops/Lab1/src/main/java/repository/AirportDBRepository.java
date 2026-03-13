package repository;

import domain.Airport;
import utils.DatabaseManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class AirportDBRepository implements IAirportRepository {
    private final DatabaseManager databaseManager;

    public AirportDBRepository(Properties properties) {
        databaseManager = new DatabaseManager(properties);
    }

    @Override
    public Optional<Airport> save(Airport airport) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO airports (Name, City, Country) VALUES (?, ?, ?) RETURNING AirportID")) {
            preparedStatement.setString(1, airport.getName());
            preparedStatement.setString(2, airport.getCity());
            preparedStatement.setString(3, airport.getCountry());
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int AirportID = resultSet.getInt("AirportID");
                return Optional.of(new Airport(AirportID, airport.getName(), airport.getCity(), airport.getCountry()));
            } else {
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error saving airport", e);
        }
    }

    @Override
    public void deleteById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM airports WHERE AirportID = ?")) {
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Airport findById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM airports WHERE AirportID = ?")) {
            preparedStatement.setInt(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int AirportID = resultSet.getInt("AirportID");
                String Name = resultSet.getString("Name");
                String City = resultSet.getString("City");
                String Country = resultSet.getString("Country");
                return new Airport(AirportID, Name, City, Country);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public List<Airport> findAll() {
        List<Airport> airports = new ArrayList<>();
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM airports")) {
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                int AirportID = resultSet.getInt("AirportID");
                String Name = resultSet.getString("Name");
                String City = resultSet.getString("City");
                String Country = resultSet.getString("Country");
                airports.add(new Airport(AirportID, Name, City, Country));
            }
            return airports;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return airports;
    }

    @Override
    public void update(Airport airport) {
        String sql = "UPDATE airports SET Name = ?, City = ?, Country = ? WHERE AirportID = ?";
        try (Connection connection = databaseManager.getConnection();
                PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
                preparedStatement.setString(1, airport.getName());
                preparedStatement.setString(2, airport.getCity());
                preparedStatement.setString(3, airport.getCountry());
                preparedStatement.setInt(4, airport.getId());
                preparedStatement.executeUpdate();
            } catch (SQLException e) {
                e.printStackTrace();
            }
    }
}
