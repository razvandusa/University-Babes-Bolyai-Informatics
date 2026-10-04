package teme.liquibase;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import teme.liquibase.service.EmployeeService;
import teme.liquibase.ui.Console;

@SpringBootApplication
public class LiquibaseApplication implements CommandLineRunner {
    private final Console console;

    public LiquibaseApplication(Console console) {
        this.console = console;
    }

    @Override
    public void run(String... args) throws Exception {
        console.run();
    }

    public static void main(String[] args) {
        SpringApplication.run(LiquibaseApplication.class, args);
    }
}
