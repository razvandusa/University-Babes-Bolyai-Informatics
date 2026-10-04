package org.example;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.example.gui.MainViewController;
import org.example.others.ConnectionBenchmark;
import org.example.repo.CourseDBRepository;
import org.example.repo.EnrollmentDBRepository;
import org.example.repo.StudentDBRepository;
import org.example.service.Service;

public class Main extends Application {
    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage stage) throws Exception {

        ConnectionBenchmark.testWithoutPooling();
        ConnectionBenchmark.testWithPooling();

        FXMLLoader loader = new FXMLLoader(Main.class.getResource("/main-view.fxml"));
        Scene scene = new Scene(loader.load(), 800, 500);

        StudentDBRepository studentRepo = new StudentDBRepository();
        EnrollmentDBRepository enrollmentRepo = new EnrollmentDBRepository();
        CourseDBRepository courseRepo = new CourseDBRepository();
        Service service = new Service(studentRepo, enrollmentRepo, courseRepo);
        MainViewController controller = loader.getController();
        controller.setService(service);

        stage.setTitle("Lab1");
        stage.setScene(scene);
        stage.show();
    }
}