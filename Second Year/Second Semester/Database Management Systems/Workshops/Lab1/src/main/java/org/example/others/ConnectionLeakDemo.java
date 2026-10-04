package org.example.others;

import com.zaxxer.hikari.HikariConfig;
import com.zaxxer.hikari.HikariDataSource;

import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection;
import java.util.Properties;

public class ConnectionLeakDemo {

    private static HikariDataSource dataSource;

    public static void init() {
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

        config.setMaximumPoolSize(5);

        dataSource = new HikariDataSource(config);
    }

    public static void leakConnections() {
        System.out.println("STARTING LEAK TEST...");

        for (int i = 0; i < 20; i++) {
            try {
                Connection conn = dataSource.getConnection();

                System.out.println("Got connection " + i);

                Thread.sleep(200);

            } catch (Exception e) {
                System.out.println("FAILED at iteration " + i);
                System.out.println(e.getMessage());
            }
        }
    }

    public static void main(String[] args) {
        init();
        leakConnections();
    }
}
