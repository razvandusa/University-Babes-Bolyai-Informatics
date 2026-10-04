package org.example;

import java.sql.*;
import java.util.Properties;

public class LostUpdate {
    private String url;
    private String user;
    private String pass;

    public LostUpdate(Properties props) {
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

        lostUpdate();

        System.out.println();
        System.out.println("---------------------------");
        System.out.println();

        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
        }

        lostUpdateSolved();
    }

    private void lostUpdate() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement ps1 = conn.prepareStatement("SELECT salary FROM employees WHERE id = 1");
                ResultSet rs1 = ps1.executeQuery();
                double salary = 0;
                if (rs1.next()) {
                    salary = rs1.getDouble("salary");
                    System.out.println("[A] Salariu citit: " + salary);
                }
                double newSalary = salary + 1000;

                synchronized (lock1) {
                    lock1.notifyAll();
                }
                synchronized (lock2) {
                    try {
                        lock2.wait(3000);
                    } catch (InterruptedException e) {}
                }

                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees SET salary = ? WHERE id = 1");
                update.setDouble(1, newSalary);
                update.executeUpdate();
                System.out.println("[A] Salariu actualizat la " + newSalary);

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

                PreparedStatement ps1 = conn.prepareStatement("SELECT salary FROM employees WHERE id = 1");
                ResultSet rs1 = ps1.executeQuery();
                double salary = 0;
                if (rs1.next()) {
                    salary = rs1.getDouble("salary");
                    System.out.println("[B] Salariu citit: " + salary);
                }
                double newSalary = salary + 500;

                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees SET salary = ? WHERE id = 1");
                update.setDouble(1, newSalary);
                update.executeUpdate();
                System.out.println("[B] Salariu actualizat la " + newSalary);

                conn.commit();
                System.out.println("[B] COMMIT");
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

    private void lostUpdateSolved() {
        Object lock = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement ps1 = conn.prepareStatement("SELECT salary FROM employees WHERE id = 1 FOR UPDATE");
                ResultSet rs1 = ps1.executeQuery();
                double salary = 0;
                if (rs1.next()) {
                    salary = rs1.getDouble("salary");
                    System.out.println("[A] Rand blocat + salariu citit: " + salary);
                }

                synchronized (lock) {
                    lock.notifyAll();
                }
                Thread.sleep(2000);

                double newSalary = salary + 1000;
                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees SET salary = ? WHERE id = 1");
                update.setDouble(1, newSalary);
                update.executeUpdate();
                System.out.println("[A] Salariu actualizat la " + newSalary);

                conn.commit();
                System.out.println("[A] COMMIT + rand deblocat");
            } catch (SQLException | InterruptedException e) {
                e.printStackTrace();
            }
        });

        Thread transB = new Thread(() -> {
            synchronized (lock) {
                try {
                    lock.wait(3000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] BEGIN TRANSACTION");

                PreparedStatement select = conn.prepareStatement(
                        "SELECT salary FROM employees WHERE id = 1 FOR UPDATE");
                ResultSet rs = select.executeQuery();
                double salary = 0;
                if (rs.next()) {
                    salary = rs.getDouble("salary");
                    System.out.println("[B] Randul s-a deblocat, am citit salariul actualizat: " + salary);
                }

                double newSalary = salary + 500;
                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees SET salary = ? WHERE id = 1");
                update.setDouble(1, newSalary);
                update.executeUpdate();
                conn.commit();
                System.out.println("[B] Am scris salariul: " + newSalary + " si am dat commit");

            } catch (SQLException e) {
                System.out.println("[B] Eroare: " + e.getMessage());
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
