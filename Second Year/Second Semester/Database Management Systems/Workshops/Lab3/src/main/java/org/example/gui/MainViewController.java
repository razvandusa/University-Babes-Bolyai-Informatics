package org.example.gui;

import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import org.example.domain.Course;
import org.example.domain.Enrollment;
import org.example.domain.Student;
import org.example.service.Service;

import java.util.List;

public class MainViewController {
    private Service service;

    @FXML
    private TableView<Student> studentsTable;
    @FXML
    private TableColumn<Student, String> idColumn;
    @FXML
    private TableColumn<Student, String> nameColumn;
    @FXML
    private TableColumn<Student, String> ageColumn;

    @FXML
    private TableView<Enrollment> enrollmentTable;
    @FXML
    private TableColumn<Enrollment, String> studentIdColumn;
    @FXML
    private TableColumn<Enrollment, String> courseIdColumn;
    @FXML
    private TableColumn<Enrollment, String> gradeColumn;
    @FXML
    private TextField studentIdField;
    @FXML
    private TextField courseIdField;
    @FXML
    private TextField gradeField;

    @FXML
    public void initialize() {
        configureColumns();
        addStudentsTableClickListener();
        addEnrollmentTableClickListener();
    }

    private void configureColumns() {
        idColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getId())));
        nameColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(param.getValue().getName()));
        ageColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getAge())));
        studentIdColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getStudent().getId())));
        courseIdColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getCourse().getId())));
        gradeColumn.setCellValueFactory(param -> new javafx.beans.property.SimpleStringProperty(String.valueOf(param.getValue().getGrade())));
    }

    private void addStudentsTableClickListener() {
        // Add listener to the students table to update the enrollment table when a student is selected
        studentsTable.getSelectionModel()
                .selectedItemProperty()
                .addListener((obs, oldSelection, student) -> {
                    if (student != null) {
                        studentIdField.setText(String.valueOf(student.getId()));
                        List<Enrollment> enrollments = service.getEnrollmentsByStudentId(student.getId());
                        enrollmentTable.setItems(FXCollections.observableArrayList(enrollments));
                    }
                });
    }

    private void addEnrollmentTableClickListener() {
        enrollmentTable.getSelectionModel()
                .selectedItemProperty()
                .addListener((obs, oldSelection, enrollment) -> {
                    if (enrollment != null) {
                        courseIdField.setText(String.valueOf(enrollment.getCourse().getId()));
                        gradeField.setText(String.valueOf(enrollment.getGrade()));
                    }
                });
    }

    public void setService(Service service) {
        this.service = service;
        initializeData();
    }

    private void initializeData() {
        studentsTable.setItems(FXCollections.observableArrayList(service.getAllStudents()));
    }

    @FXML
    private void addEnrollment() {
        if (studentsTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Student not selected");
            alert.setContentText("You must select a student from the students table before adding an enrollment.");
            alert.showAndWait();
            return;
        }
        if (courseIdField.getText().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Course ID not entered");
            alert.setContentText("You must enter a course ID before adding an enrollment.");
            alert.showAndWait();
            return;
        }
        if (gradeField.getText().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Grade not entered");
            alert.setContentText("You must enter a grade before adding an enrollment.");
            alert.showAndWait();
            return;
        }
        Student student = studentsTable.getSelectionModel().getSelectedItem();
        int courseId = Integer.parseInt(courseIdField.getText());
        Course course = service.getCourseById(courseId);
        int grade = Integer.parseInt(gradeField.getText());
        Enrollment enrollment = new Enrollment(student, course, grade);
        try {
            service.addEnrollment(enrollment);
            studentIdField.clear();
            courseIdField.clear();
            gradeField.clear();
            enrollmentTable.setItems(FXCollections.observableArrayList(service.getEnrollmentsByStudentId(student.getId())));
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Exception");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    private void editEnrollment() {
        if (enrollmentTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Enrollment not selected");
            alert.setContentText("You must select a row from the enrollments table before editing an enrollment.");
            alert.showAndWait();
            return;
        }
        if (studentIdField.getText().isEmpty() || courseIdField.getText().isEmpty() || gradeField.getText().isEmpty()) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Student ID or Course ID or grade not entered");
            alert.setContentText("You must enter student ID, course ID and grade before editing an enrollment.");
            alert.showAndWait();
            return;
        }
        Enrollment selectedEnrollment = enrollmentTable.getSelectionModel().getSelectedItem();
        String studentId = studentIdField.getText();
        Student student = service.getStudentById(Integer.parseInt(studentId));
        Integer courseId = Integer.parseInt(courseIdField.getText());
        Course course = service.getCourseById(courseId);
        if (course == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Course not found");
            alert.setContentText("Course with ID " + courseId + " not found.");
            alert.showAndWait();
            return;
        }
        Integer grade = Integer.parseInt(gradeField.getText());
        Enrollment newEnrollment = new Enrollment(student, course, grade);
        try {
            service.updateEnrollment(selectedEnrollment, newEnrollment);
            enrollmentTable.setItems(FXCollections.observableArrayList(service.getEnrollmentsByStudentId(newEnrollment.getStudent().getId())));
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    private void deleteEnrollment() {
        if (enrollmentTable.getSelectionModel().getSelectedItem() == null) {
            Alert alert = new Alert(Alert.AlertType.WARNING);
            alert.setTitle("Warning");
            alert.setHeaderText("Enrollment not selected");
            alert.setContentText("You must select a row from the enrollments table before deleting an enrollment.");
            alert.showAndWait();
            return;
        }
        Enrollment enrollment = enrollmentTable.getSelectionModel().getSelectedItem();
        service.deleteEnrollment(enrollment);
        enrollmentTable.setItems(FXCollections.observableArrayList(service.getEnrollmentsByStudentId(enrollment.getStudent().getId())));
    }
}