package org.example.gui;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import org.example.domain.Employee;
import org.example.service.Service;

import java.util.List;

public class KeysetPaginationController {
    private Service service;
    @FXML private TableView<Employee> employeeTable;
    @FXML private TableColumn<Employee, String> idColumn;
    @FXML private TableColumn<Employee, String> emailColumn;
    @FXML private TableColumn<Employee, String> salaryColumn;
    @FXML private TableColumn<Employee, String> departmentNameColumn;
    @FXML private Button btnLoadMore;
    @FXML private Label statusLabel;

    private int pageSize = 20;
    private Integer lastId = 0;
    private int loadedCount = 0;

    @FXML
    public void initialize() {
        idColumn.setCellValueFactory(new PropertyValueFactory<>("id"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        salaryColumn.setCellValueFactory(new PropertyValueFactory<>("salary"));
        departmentNameColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getDepartment().getName()));
        employeeTable.setSelectionModel(null);
    }

    public void setService(Service service) {
        this.service = service;
    }

    public void loadFirstBatch() {
        handleLoadMore();
    }

    @FXML
    private void handleLoadMore() {
        long startTime = System.currentTimeMillis();
        List<Employee> nextBatch = service.getEmployeesByKeyset(Long.valueOf(lastId), pageSize);

        if (!nextBatch.isEmpty()) {
            lastId = nextBatch.get(nextBatch.size() - 1).getId();
            employeeTable.getItems().addAll(nextBatch);
            loadedCount += nextBatch.size();
            long endTime = System.currentTimeMillis();
            statusLabel.setText("Loaded " + loadedCount + " employees in " + (endTime - startTime) + " ms");
        }
        else {
            btnLoadMore.setDisable(true);
            statusLabel.setText("No more employees to load");
        }
    }
}
