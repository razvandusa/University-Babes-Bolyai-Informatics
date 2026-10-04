package org.example.repo;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

public class DatabaseManager {
    private final Properties jdbcProps;
    private Connection instance = null;

    public DatabaseManager(Properties props) {
        this.jdbcProps = props;
    }

    /**
     * Get a new connection to the database
     * @return Connection
     */
    private Connection getNewConnection() {
        //extract db configuration properties
        String url = jdbcProps.getProperty("jdbc.url");
        String user = jdbcProps.getProperty("jdbc.user");
        String password = jdbcProps.getProperty("jdbc.pass");
        Connection conn = null;
        //get connection depending on the type of database used
        try {
            if (user != null && password != null)
                conn = DriverManager.getConnection(url, user, password);
            else
                conn = DriverManager.getConnection(url);
        } catch (SQLException e) {
            System.out.println("Error getting connection " + e.getMessage());
        }
        return conn;
    }

    /**
     * Get a connection to the database
     * @return Connection
     */
    public Connection getConnection() {
        //if connection is null or closed, get a new connection
        //otherwise return the existing connection
        try {
            if (instance == null || instance.isClosed())
                instance = getNewConnection();
        } catch (SQLException e) {
            System.out.println("Error getting connection " + e.getMessage());
        }
        return instance;
    }
}
