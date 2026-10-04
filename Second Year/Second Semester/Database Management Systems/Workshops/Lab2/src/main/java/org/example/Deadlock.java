package org.example;

import java.sql.*;
import java.util.Properties;

public class Deadlock {
    private String url;
    private String user;
    private String pass;

    public Deadlock(Properties props) {
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
            stmt.execute("INSERT INTO employees (id, name, salary, department_id) VALUES (2, 'Jane', 5500, 1);");
        }
    }

    public void run() {
        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        deadlock();

        System.out.println();
        System.out.println("---------------------------");
        System.out.println();

        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        deadlockSolved();
    }

    private void deadlock() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement ps1 = conn.prepareStatement(
                        "UPDATE employees SET salary = 6000 WHERE id = 1");
                ps1.executeUpdate();
                System.out.println("[A] I blocked id=1");

                synchronized (lock1) { lock1.notifyAll(); }
                synchronized (lock2) {
                    try { lock2.wait(3000); } catch (InterruptedException ignored) {}
                }

                System.out.println("[A] I also try to block id=2");
                PreparedStatement ps2 = conn.prepareStatement(
                        "UPDATE employees SET salary = 7000 WHERE id = 2");
                ps2.executeUpdate();
                conn.commit();
                System.out.println("[A] Commit made");

            } catch (SQLException e) {
                System.out.println("[A] Deadlock detected: " + e.getMessage());
                System.out.println("[A] Transaction A was chosen as victim, rollback");
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

                PreparedStatement ps1 = conn.prepareStatement(
                        "UPDATE employees SET salary = 6000 WHERE id = 2");
                ps1.executeUpdate();
                System.out.println("[B] I blocked id=2");

                synchronized (lock2) { lock2.notifyAll(); }
                Thread.sleep(500);

                System.out.println("[B] I also try to block id=1");
                PreparedStatement ps2 = conn.prepareStatement(
                        "UPDATE employees SET salary = 7000 WHERE id = 1");
                ps2.executeUpdate();
                conn.commit();
                System.out.println("[B] Commit made");

            } catch (SQLException e) {
                System.out.println("[B] Deadlock detected: " + e.getMessage());
                System.out.println("[B] Transaction B was chosen as victim, rollback");
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });

        transA.start();
        transB.start();
        try { transA.join(10000); transB.join(10000); }
        catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void deadlockSolved() {
        Thread transactionA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION (good order: id=1, id=2)");

                PreparedStatement ps1 = conn.prepareStatement("UPDATE employees SET salary = 6000 WHERE id = 1");
                ps1.executeUpdate();
                System.out.println("[A] I blocked and updated with id=1");

                Thread.sleep(500);

                PreparedStatement ps2 = conn.prepareStatement("UPDATE employees SET salary = 7000 WHERE id = 2");
                ps2.executeUpdate();
                System.out.println("[A] I blocked and updated with id=2");

                conn.commit();
                System.out.println("[A] Commit made, without deadlock");

            } catch (SQLException | InterruptedException e) {
                System.out.println("[A] Erorr: " + e.getMessage());
            }
        });

        Thread transactionB = new Thread(() -> {
            try { Thread.sleep(200); } catch (InterruptedException ignored) {}

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] BEGIN TRANSACTION (good order: id=1, id=2)");

                PreparedStatement ps1 = conn.prepareStatement("UPDATE employees SET salary = 8000 WHERE id = 1");
                ps1.executeUpdate();
                System.out.println("[B] I blocked and updated id=1 (after A)");

                PreparedStatement ps2 = conn.prepareStatement(
                        "UPDATE employees SET salary = 9000 WHERE id = 2");
                ps2.executeUpdate();
                System.out.println("[B] I blocked and updated id=2");

                conn.commit();
                System.out.println("[B] Commit made, without deadlock");

            } catch (SQLException e) {
                System.out.println("[B] Error: " + e.getMessage());
            }
        });

        transactionA.start();
        transactionB.start();
        try { transactionA.join(10000); transactionB.join(10000); }
        catch (InterruptedException ignored) {}
    }
}
