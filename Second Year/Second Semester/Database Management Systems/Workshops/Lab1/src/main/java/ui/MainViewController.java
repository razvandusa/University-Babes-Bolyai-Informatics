package ui;

import domain.Airplane;
import domain.Flight;
import dto.FlightDTO;
import dto.FlightFilterDTO;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import service.IAirplaneService;
import service.IAirportService;
import service.IFlightService;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

public class MainViewController {
    private IAirplaneService airplaneService;
    private IAirportService airportService;
    private IFlightService flightService;

    @FXML
    private TableView<Airplane> airplanesTable;
    @FXML
    private TableColumn<Airplane, String> airplaneIDColumn;
    @FXML
    private TableColumn<Airplane, String> modelColumn;
    @FXML
    private TableColumn<Airplane, String> capacityColumn;

    @FXML
    private TableView<Flight> flightsTable;
    @FXML
    private TableColumn<Flight, String> flightIDColumn;
    @FXML
    private TableColumn<Flight, String> flightAirplaneIDColumn;
    @FXML
    private TableColumn<Flight, String> departureAirportIDColumn;
    @FXML
    private TableColumn<Flight, String> arrivalAirportIDColumn;
    @FXML
    private TableColumn<Flight, String> departureDateTimeColumn;
    @FXML
    private TableColumn<Flight, String> arrivalDateTimeColumn;

    @FXML
    private TextField departureAirportIDTextField;
    @FXML
    private TextField arrivalAirportIDTextField;
    @FXML
    private TextField departureDateTimeTextField;
    @FXML
    private TextField arrivalDateTimeTextField;


    @FXML
    public void initialize() {
        columnsConfiguration();
    }

    private void columnsConfiguration() {
        airplaneIDColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getId())));
        modelColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getModel()));
        capacityColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getCapacity())));

        flightIDColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getId())));
        flightAirplaneIDColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getAirplaneID())));
        departureAirportIDColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getDepartureAirportID())));
        arrivalAirportIDColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getArrivalAirportID())));
        departureDateTimeColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getDepartureDateTime().toString()));
        arrivalDateTimeColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getArrivalDateTime().toString()));
    }

    public void setService(IAirplaneService airplaneService, IAirportService airportService, IFlightService flightService) {
        this.airplaneService = airplaneService;
        this.airportService = airportService;
        this.flightService = flightService;
        this.loadTables();
        this.airplaneTableClickListener();
        this.flightTableClickListener();
    }

    private void loadTables() {
        flightsTable.setItems(FXCollections.observableArrayList(flightService.getAllFlights()));
        airplanesTable.setItems(FXCollections.observableArrayList(airplaneService.getAllAirplanes()));
    }

    private void airplaneTableClickListener() {
        airplanesTable.getSelectionModel()
                .selectedItemProperty()
                .addListener((observable, oldAirplane, newAirplane) -> {
                   if (newAirplane != null) {
                       List<Flight> flights = flightService.getAllFlights(new FlightFilterDTO(newAirplane.getId(), null, null, null, null));
                       flightsTable.setItems(FXCollections.observableArrayList(flights));
                   }
                });
    }

    private void flightTableClickListener() {
        flightsTable.getSelectionModel()
                .selectedItemProperty()
                .addListener((observable, oldFlight, newFlight) -> {
                   if (newFlight != null) {
                       DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                       departureAirportIDTextField.setText(String.valueOf(newFlight.getDepartureAirportID()));
                       arrivalAirportIDTextField.setText(String.valueOf(newFlight.getArrivalAirportID()));
                       departureDateTimeTextField.setText(newFlight.getDepartureDateTime().format(formatter));
                       arrivalDateTimeTextField.setText(newFlight.getArrivalDateTime().format(formatter));
                   }
                });
    }

    @FXML
    private void addFlight() {
        if (airplanesTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("No airplane selected");
            alert.setContentText("Please select an airplane from the table in order to add a flight.");
            alert.showAndWait();
            return;
        }
        if (airportService.getAirportById(Integer.parseInt(departureAirportIDTextField.getText())) == null || airportService.getAirportById(Integer.parseInt(arrivalAirportIDTextField.getText())) == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Invalid airport ID");
            alert.setContentText("Please enter a valid airport ID.");
            alert.showAndWait();
            return;
        }
        if (departureAirportIDTextField.getText().isEmpty() || arrivalAirportIDTextField.getText().isEmpty() || departureDateTimeTextField.getText().isEmpty() || arrivalDateTimeTextField.getText().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Missing fields");
            alert.setContentText("Please fill in all fields.");
            alert.showAndWait();
        }
        try {
            Integer departureAirportID = Integer.parseInt(departureAirportIDTextField.getText());
        } catch (NumberFormatException e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Invalid departure airport ID");
            alert.setContentText("Please enter a valid departure airport ID.");
            alert.showAndWait();
        }
        try {
            Integer arrivalAirportID = Integer.parseInt(arrivalAirportIDTextField.getText());
        } catch (NumberFormatException e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Invalid arrival airport ID");
            alert.setContentText("Please enter a valid arrival airport ID.");
            alert.showAndWait();
        }
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            LocalDateTime departureDateTime = LocalDateTime.parse(departureDateTimeTextField.getText(), formatter);
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Invalid departure date and time");
            alert.setContentText("Please enter a valid departure date and time.");
            alert.showAndWait();
        }
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            LocalDateTime arrivalDateTime = LocalDateTime.parse(arrivalDateTimeTextField.getText(), formatter);
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Invalid arrival date and time");
            alert.setContentText("Please enter a valid arrival date and time.");
            alert.showAndWait();
        }
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            FlightDTO flight = new FlightDTO(
                    airplanesTable.getSelectionModel().getSelectedItem().getId(),
                    Integer.parseInt(departureAirportIDTextField.getText()),
                    Integer.parseInt(arrivalAirportIDTextField.getText()),
                    LocalDateTime.parse(departureDateTimeTextField.getText(), formatter),
                    LocalDateTime.parse(arrivalDateTimeTextField.getText(), formatter)
            );
            flightService.createFlight(flight);
            flightsTable.setItems(FXCollections.observableArrayList(flightService.getAllFlights(new FlightFilterDTO(airplanesTable.getSelectionModel().getSelectedItem().getId(), null, null, null, null))));
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error adding flight");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    private void deleteFlight() {
        if (flightsTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("No flight selected");
            alert.setContentText("Please select a flight from the table in order to delete it.");
            alert.showAndWait();
            return;
        }
        try {
            flightService.deactivateFlight(flightsTable.getSelectionModel().getSelectedItem().getId());
            flightsTable.setItems(FXCollections.observableArrayList(flightService.getAllFlights(new FlightFilterDTO(airplanesTable.getSelectionModel().getSelectedItem().getId(), null, null, null, null))));
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error deleting flight");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    private void editFlight() {
        if (flightsTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("No flight selected");
            alert.setContentText("Please select a flight from the table in order to edit it.");
            alert.showAndWait();
            return;
        }
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
            FlightDTO flight = new FlightDTO(
                    flightsTable.getSelectionModel().getSelectedItem().getId(),
                    Integer.parseInt(departureAirportIDTextField.getText()),
                    Integer.parseInt(arrivalAirportIDTextField.getText()),
                    LocalDateTime.parse(departureDateTimeTextField.getText(), formatter),
                    LocalDateTime.parse(arrivalDateTimeTextField.getText(), formatter)
            );
            flightService.updateFlight(flightsTable.getSelectionModel().getSelectedItem().getId(), flight);
            flightsTable.setItems(FXCollections.observableArrayList(flightService.getAllFlights(new FlightFilterDTO(flightsTable.getSelectionModel().getSelectedItem().getId(), null, null, null, null))));
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setHeaderText("Error editing flight");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
}
