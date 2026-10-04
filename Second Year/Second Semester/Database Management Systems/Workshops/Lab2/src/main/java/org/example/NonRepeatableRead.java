package org.example;

import java.sql.*;
import java.util.Properties;

public class NonRepeatableRead {
    private String url;
    private String user;
    private String pass;

    public NonRepeatableRead(Properties props) {
        this.url = props.getProperty("jdbc.url");
        this.user = props.getProperty("jdbc.user");
        this.pass = props.getProperty("jdbc.pass");
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(url, user, pass);
    }

    private void setup() throws SQLException {
        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {
            stmt.execute("DELETE FROM employees WHERE id >= 1;");
            stmt.execute("INSERT INTO employees (id, name, salary, department_id) VALUES (1, 'John', 5000, 1);");
        }
    }

    public void run() {
        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        nonRepeatableRead();

        System.out.println();
        System.out.println("---------------------------");
        System.out.println();

        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {
            stmt.execute("UPDATE employees SET salary = 5000.00 WHERE id = 1");
        } catch (SQLException e) {
            e.printStackTrace();
        }

        nonRepeatableReadSolved();
    }

    private void nonRepeatableRead() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                conn.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
                System.out.println("[A] BEGIN TRANSACTION (READ COMMITTED)");

                PreparedStatement ps = conn.prepareStatement("SELECT * FROM employees WHERE id = 1");
                ResultSet rs1 = ps.executeQuery();
                if (rs1.next()) {
                    System.out.println("[A] Salariu citit: " + rs1.getDouble("salary"));
                }

                synchronized (lock1) {
                    lock1.notifyAll();
                }
                synchronized (lock2) {
                    try {
                        lock2.wait(3000);
                    } catch (InterruptedException e) {}
                }

                ResultSet rs2 = ps.executeQuery();
                if (rs2.next()) {
                    System.out.println("[A] Salariu citit: " + rs2.getDouble("salary") + " <-- NON-REPEATABLE READ!");
                }

                conn.commit();
                System.out.println("[A] COMMIT");

            } catch (SQLException e) {
                e.printStackTrace();
            }
        });

        Thread transB = new Thread(() -> {
            synchronized (lock1) {
                try {
                    lock1.wait(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] BEGIN TRANSACTION");

                PreparedStatement ps = conn.prepareStatement("UPDATE employees SET salary = 12000 WHERE id = 1");
                ps.executeUpdate();
                conn.commit();
                System.out.println("[B] Salariu actualizat la 12000 (comis)");

            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                synchronized (lock2) {
                    lock2.notifyAll();
                }
            }
        });

        transA.start();
        transB.start();
        try {
            transA.join();
            transB.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void nonRepeatableReadSolved() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                conn.setTransactionIsolation(Connection.TRANSACTION_REPEATABLE_READ);
                System.out.println("[A] BEGIN TRANSACTION (REPEATABLE READ)");

                PreparedStatement ps = conn.prepareStatement("SELECT * FROM employees WHERE id = 1");
                ResultSet rs1 = ps.executeQuery();
                if (rs1.next()) {
                    System.out.println("[A] Salariu citit: " + rs1.getDouble("salary"));
                }

                synchronized (lock1) {
                    lock1.notifyAll();
                }
                synchronized (lock2) {
                    try {
                        lock2.wait(3000);
                    } catch (InterruptedException e) {}
                }

                ResultSet rs2 = ps.executeQuery();
                if (rs2.next()) {
                    System.out.println("[A] Salariu citit: " + rs2.getDouble("salary") + " <-- aceeasi valoare din cauza REPEATABLE READ!");
                }

                conn.commit();
                System.out.println("[A] COMMIT");

            } catch (SQLException e) {
                e.printStackTrace();
            }
        });

        Thread transB = new Thread(() -> {
            synchronized (lock1) {
                try {
                    lock1.wait(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] BEGIN TRANSACTION");

                PreparedStatement ps = conn.prepareStatement("UPDATE employees SET salary = 12000 WHERE id = 1");
                ps.executeUpdate();
                conn.commit();
                System.out.println("[B] Salariu actualizat la 12000 (comis)");

            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                synchronized (lock2) {
                    lock2.notifyAll();
                }
            }
        });

        transA.start();
        transB.start();
        try {
            transA.join();
            transB.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
