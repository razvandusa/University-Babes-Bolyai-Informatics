package org.example;

import java.sql.*;
import java.util.Properties;

public class DirtyRead {
    private String url;
    private String user;
    private String pass;

    public DirtyRead(Properties props) {
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
            stmt.execute("CREATE TABLE IF NOT EXISTS employees_dirty (id INT PRIMARY KEY, salary DOUBLE)");
            stmt.execute("INSERT INTO employees_dirty (id, salary) VALUES (1, 5000) AS new_data ON DUPLICATE KEY UPDATE salary = new_data.salary;");
        }
    }

    public void run() {
        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        dirtyRead();

        System.out.println();
        System.out.println("---------------------------");
        System.out.println();

        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {
            stmt.execute("UPDATE employees_dirty SET salary = 5000.00 WHERE id = 1");
        } catch (SQLException e) {
            e.printStackTrace();
        }

        dirtyReadSolved();
    }

    private void dirtyRead() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees_dirty SET salary = 10000 WHERE id = 1");
                update.executeUpdate();
                System.out.println("[A] Salariu actualizat la 10000 (ne-comis)");

                synchronized (lock1) {
                    lock1.notifyAll();
                }
                synchronized (lock2) {
                    try {
                        lock2.wait(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                conn.rollback();
                System.out.println("[A] ROLLBACK! Salariu resetat la 5000");

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
                conn.setTransactionIsolation(Connection.TRANSACTION_READ_UNCOMMITTED);
                conn.setAutoCommit(false);

                System.out.println("[B] BEGIN TRANSACTION (READ UNCOMMITTED)");

                PreparedStatement select = conn.prepareStatement(
                        "SELECT salary FROM employees_dirty WHERE id = 1");
                ResultSet rs = select.executeQuery();
                if (rs.next()) {
                    System.out.println("[B] Salariu citit: " + rs.getDouble("salary")
                            + " <-- DIRTY READ! Uncommited data!");
                }

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

        try (Connection conn = getConnection();
             PreparedStatement ps = conn.prepareStatement(
                     "SELECT salary FROM employees_dirty WHERE id = 1");
             ResultSet rs = ps.executeQuery()) {
            if (rs.next())
                System.out.println("[FINAL] Salariu in BD: " + rs.getDouble("salary")
                        + " (B a citit o valoare care nu a existat niciodata!)");
        } catch (SQLException e) {
            System.out.println("Eroare: " + e.getMessage());
        }
    }

    private void dirtyReadSolved() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement update = conn.prepareStatement(
                        "UPDATE employees_dirty SET salary = 10000 WHERE id = 1");
                update.executeUpdate();
                System.out.println("[A] Salariu actualizat la 10000 (ne-comis)");

                synchronized (lock1) {
                    lock1.notifyAll();
                }
                synchronized (lock2) {
                    try {
                        lock2.wait(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                conn.rollback();
                System.out.println("[A] ROLLBACK! Salariu resetat la 5000");

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
                conn.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
                conn.setAutoCommit(false);

                System.out.println("[B] BEGIN TRANSACTION (READ COMMITTED)");

                PreparedStatement select = conn.prepareStatement(
                        "SELECT salary FROM employees_dirty WHERE id = 1");
                ResultSet rs = select.executeQuery();
                if (rs.next()) {
                    System.out.println("[B] Salariu citit: " + rs.getDouble("salary")
                            + " <-- valoare corecta!");
                }

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
}
