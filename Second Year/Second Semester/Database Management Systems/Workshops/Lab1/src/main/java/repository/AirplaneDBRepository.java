package repository;

import domain.Airplane;
import utils.DatabaseManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.Properties;

public class AirplaneDBRepository implements IAirplaneRepository {
    private final DatabaseManager databaseManager;

    public AirplaneDBRepository(Properties properties) {
        databaseManager = new DatabaseManager(properties);
    }

    @Override
    public Optional<Airplane> save(Airplane airplane) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("INSERT INTO airplanes (Model, Capacity) VALUES (?, ?) RETURNING AirplaneID")) {
            preparedStatement.setString(1, airplane.getModel());
            preparedStatement.setInt(2, airplane.getCapacity());

            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int AirplaneID = resultSet.getInt("AirplaneID");
                return Optional.of(new Airplane(AirplaneID, airplane.getModel(), airplane.getCapacity()));
            } else {
                return Optional.empty();
            }
        } catch (SQLException e) {
            throw new RuntimeException("Error saving airplane", e);
        }
    }

    @Override
    public void deleteById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("DELETE FROM airplanes WHERE AirplaneID = ?")) {
            preparedStatement.setInt(1, id);
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Airplane findById(Integer id) {
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM airplanes WHERE AirplaneID = ?")) {
            preparedStatement.setInt(1, id);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                int AirplaneID = resultSet.getInt("AirplaneID");
                String Model = resultSet.getString("Model");
                int Capacity = resultSet.getInt("Capacity");
                return new Airplane(AirplaneID, Model, Capacity);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public List<Airplane> findAll() {
        List<Airplane> airplanes = new ArrayList<>();
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM airplanes")) {
            ResultSet resultSet = preparedStatement.executeQuery();
            while (resultSet.next()) {
                int AirplaneID = resultSet.getInt("AirplaneID");
                String Model = resultSet.getString("Model");
                int Capacity = resultSet.getInt("Capacity");
                airplanes.add(new Airplane(AirplaneID, Model, Capacity));
            }
            return airplanes;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return airplanes;
    }

    @Override
    public void update(Airplane airplane) {
        String sql = "UPDATE airplanes SET Model = ?, Capacity = ? WHERE AirplaneID = ?";
        try (Connection connection = databaseManager.getConnection();
             PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, airplane.getModel());
            preparedStatement.setInt(2, airplane.getCapacity());
            preparedStatement.setInt(3, airplane.getId());
            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            throw new RuntimeException("Error updating airplane", e);
        }
    }
}
