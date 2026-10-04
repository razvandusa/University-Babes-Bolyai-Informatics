package org.example.gui;

import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.domain.Employee;
import org.example.service.Service;

import java.util.List;

public class OffsetPaginationController {
    private Service service;
    @FXML private TableView<Employee> employeeTable;
    @FXML private TableColumn<Employee, String> idColumn;
    @FXML private TableColumn<Employee, String> emailColumn;
    @FXML private TableColumn<Employee, String> salaryColumn;
    @FXML private TableColumn<Employee, String> departmentNameColumn;
    @FXML private Label labelForPageSize;
    @FXML private ComboBox<String> pageSizeSelector;
    @FXML private Label pageNumber;
    @FXML private Label statsLabel;

    private int currentPage = 1;
    private int pageSize = 10;
    private int totalPages;

    @FXML
    private void initialize() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        salaryColumn.setCellValueFactory(new PropertyValueFactory<>("salary"));
        departmentNameColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getDepartment().getName()));
        labelForPageSize.setText("Page Size:");
        pageSizeSelector.getItems().addAll("10", "25", "50", "100");
        pageSizeSelector.getSelectionModel().select("10");
        pageSizeSelector.setOnAction(event -> {
           pageSize = Integer.parseInt(pageSizeSelector.getValue());
           currentPage = 1;
           initializePagination();
           loadPage(1);
        });
    }

    public void setService(Service service) {
        this.service = service;
    }

    public void loadData() {
        initializePagination();
        initializeData();
        updatePageLabel();
    }

    private void initializePagination() {
        totalPages = (int) Math.ceil(service.getEmployeeCount() / (double) pageSize);
    }

    private void initializeData() {
        loadPage(1);
    }

    private void loadPage(int page) {
        if (page < 1 || page > totalPages) {
            return;
        }
        long startTime = System.currentTimeMillis();
        currentPage = page;
        List<Employee> employees = service.getEmployeesByOffset(currentPage, pageSize);
        if (employees != null) {
            employeeTable.setItems(FXCollections.observableArrayList(employees));
            long endTime = System.currentTimeMillis();
            statsLabel.setText("Loaded " + employees.size() + " employees in " + (endTime - startTime) + " ms");
        }
        updatePageLabel();
    }

    private void updatePageLabel() {
        pageNumber.setText("Page " + currentPage + " / " + totalPages);
    }

    @FXML
    private void firstPage(ActionEvent actionEvent) {
        loadPage(1);
    }

    @FXML
    private void onPreviousPage(ActionEvent actionEvent) {
        if (currentPage > 1) {
            loadPage(currentPage - 1);
        }
    }

    @FXML
    private void middlePage(ActionEvent actionEvent) {
        loadPage(totalPages / 2);
    }

    @FXML
    private void onNextPage(ActionEvent actionEvent) {
        if (currentPage < totalPages) {
            loadPage(currentPage + 1);
        }
    }

    @FXML
    private void lastPage(ActionEvent actionEvent) {
        loadPage(totalPages);
    }
}
