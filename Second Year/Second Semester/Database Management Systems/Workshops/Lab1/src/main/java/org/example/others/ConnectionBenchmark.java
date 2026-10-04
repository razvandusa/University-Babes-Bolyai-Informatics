package org.example.others;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class ConnectionBenchmark {

    public static void testWithoutPooling() {
        System.out.println("=== WITHOUT CONNECTION POOLING ===");

        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Eroare la citirea fisierului de configurare.");
            e.printStackTrace();
            return;
        }

        String url = props.getProperty("jdbc.url");
        String user = props.getProperty("jdbc.user");
        String pass = props.getProperty("jdbc.pass");

        long start = System.nanoTime();

        for (int i = 0; i < 100; i++) {
            try (Connection conn = DriverManager.getConnection(url, user, pass)) {

                // simulate minimal usage
                conn.isValid(1);

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        long end = System.nanoTime();

        printResults(start, end, "Without Pooling");
    }

    public static void testWithPooling() {
        HikariConfig config = new HikariConfig();

        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Eroare la citirea fisierului de configurare.");
            e.printStackTrace();
            return;
        }

        config.setJdbcUrl(props.getProperty("jdbc.url"));
        config.setUsername(props.getProperty("jdbc.user"));
        config.setPassword(props.getProperty("jdbc.pass"));

        config.setMaximumPoolSize(10);
        config.setMinimumIdle(5);
        config.setConnectionTimeout(30000);
        HikariDataSource dataSource = new HikariDataSource(config);
        System.out.println("=== WITH HIKARI POOLING ===");

        long start = System.nanoTime();

        for (int i = 0; i < 100; i++) {
            try (Connection conn = dataSource.getConnection()) {

                conn.isValid(1);

            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        long end = System.nanoTime();

        printResults(start, end, "With Pooling");
    }

    private static void printResults(long start, long end, String label) {
        long totalTimeNs = end - start;

        double totalMs = totalTimeNs / 1_000_000.0;
        double avgMs = totalMs / 100.0;

        System.out.println("=== " + label + " RESULTS ===");
        System.out.println("Total time: " + totalMs + " ms");
        System.out.println("Average per connection: " + avgMs + " ms");
        System.out.println();
    }
}
