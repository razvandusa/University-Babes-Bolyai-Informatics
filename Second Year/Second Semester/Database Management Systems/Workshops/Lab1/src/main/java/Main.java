import dto.AirplaneDTO;
import dto.AirportDTO;
import dto.FlightDTO;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;
import repository.*;
import service.*;
import javafx.fxml.FXMLLoader;
import ui.MainViewController;
import validator.*;

import java.io.FileReader;
import java.util.Properties;

public class Main extends Application {

    private Properties getProperties() {
        Properties properties = new Properties();
        try {
            properties.load(new FileReader("bd.config"));
            return properties;
        } catch (Exception e) {
            System.out.println("Error loading database configuration: " + e.getMessage());
        }
        return properties;
    }

    @Override
    public void start(Stage stage) throws Exception {
        Properties properties = getProperties();
        IAirplaneRepository airplaneRepository = new AirplaneDBRepository(properties);
        IAirportRepository airportRepository = new AirportDBRepository(properties);
        IFlightRepository flightRepository = new FlightDBRepository(properties);
        Validator<Integer> idValidator = new IdValidator();
        Validator<AirplaneDTO> airplaneValidator = new AirplaneValidator();
        Validator<AirportDTO> airportValidator = new AirportValidator();
        Validator<FlightDTO> flightValidator = new FlightValidator();
        IAirplaneService airplaneService = new AirplaneServiceImpl(airplaneRepository, airplaneValidator, idValidator);
        IAirportService airportService = new AirportServiceImpl(airportRepository, airportValidator, idValidator);
        IFlightService flightService = new FlightServiceImpl(flightRepository, flightValidator, idValidator);

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/main-view.fxml"));
        Scene scene = new Scene(loader.load(), 1400, 400);
        MainViewController controller = loader.getController();
        controller.setService(airplaneService, airportService, flightService);

        stage.setTitle("Airline Management System");
        stage.setScene(scene);
        stage.show();
    }
}