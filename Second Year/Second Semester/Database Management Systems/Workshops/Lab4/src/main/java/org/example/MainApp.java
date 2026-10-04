package org.example;

import com.github.benmanes.caffeine.cache.Caffeine;
import jakarta.persistence.Cacheable;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.example.gui.KeysetPaginationController;
import org.example.gui.OffsetPaginationController;
import org.example.repository.DepartmentDBRepository;
import org.example.repository.EmployeeDBRepository;
import org.example.service.Service;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cache.CacheManager;
import org.springframework.cache.annotation.EnableCaching;
import org.springframework.cache.caffeine.CaffeineCacheManager;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.Bean;

import java.io.IOException;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;

@SpringBootApplication
public class MainApp extends Application {
    private static ConfigurableApplicationContext springContext;

    @Override
    public void init() {
        springContext = SpringApplication.run(MainApp.class);
    }

    @Override
    public void start(Stage stage) throws Exception {
        openOffsetsetWindow();
        openKeysetWindow();
    }

    private void openOffsetsetWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(MainApp.class.getResource("/offset-pagination-view.fxml"));
            Parent root = loader.load();

            OffsetPaginationController controller = loader.getController();
            controller.setService(springContext.getBean(Service.class));
            controller.loadData();

            Stage stage = new Stage();
            stage.setTitle("Offset Pagination");
            stage.setScene(new Scene(root));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void openKeysetWindow() {
        try {
            FXMLLoader loader = new FXMLLoader(MainApp.class.getResource("/keyset-pagination-view.fxml"));
            Parent root = loader.load();

            KeysetPaginationController controller = loader.getController();
            controller.setService(springContext.getBean(Service.class));
            controller.loadFirstBatch();

            Stage stage = new Stage();
            stage.setTitle("Keyset Pagination");
            stage.setScene(new Scene(root));
            stage.show();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void stop() {
        springContext.close();
        Platform.exit();
    }

    public static void main(String[] args) {
        Application.launch(MainApp.class, args);
    }
}
