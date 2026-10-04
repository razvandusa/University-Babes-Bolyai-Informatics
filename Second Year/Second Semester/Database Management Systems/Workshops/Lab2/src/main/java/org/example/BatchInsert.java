package org.example;

import java.sql.*;
import java.util.Arrays;
import java.util.OptionalDouble;
import java.util.Properties;

public class BatchInsert {
    private String url;
    private String user;
    private String pass;

    public BatchInsert(Properties props) {
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
        }
    }

    public void run() {
        long[] a = new long[3];
        long[] b = new long[3];
        long[] c = new long[3];

        for (int i = 0; i < 3; i++) {
            try {
                setup();
            } catch (SQLException e) {
                e.printStackTrace();
                return;
            }

            a[i] = autoCommit();

            try {
                setup();
            } catch (SQLException e) {
                e.printStackTrace();
                return;
            }

            b[i] = commitInBatches();

            try {
                setup();
            } catch (SQLException e) {
                e.printStackTrace();
                return;
            }

            c[i] = oneTimeCommit();
        }

        printResults(a, b, c);
    }

    private long autoCommit() {
        long start = System.currentTimeMillis();
        try (Connection conn = getConnection()) {
            conn.setAutoCommit(true);
            String sql = "INSERT INTO employees (id, name, salary, department_id) VALUES (?, ?, ?, ?)";

            try (PreparedStatement ps = conn.prepareStatement(sql)) {
                for (int i = 1; i <= 5000; i++) {
                    ps.setInt(1, i);
                    ps.setString(2, "Angajat " + i);
                    ps.setDouble(3, 5000.00);
                    ps.setInt(4, 1);
                    ps.executeUpdate();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        long elapsed = System.currentTimeMillis() - start;
        System.out.println("[AUTO-COMMIT] Elapsed time: " + elapsed + " ms");
        return elapsed;
    }

    private long commitInBatches() {
        long start = System.currentTimeMillis();
        try (Connection conn = getConnection()) {
            conn.setAutoCommit(false);
            String sql = "INSERT INTO employees (id, name, salary, department_id) VALUES (?, ?, ?, ?)";

            try (PreparedStatement ps = conn.prepareStatement(sql)) {
                for (int i = 1; i <= 5000; i++) {
                    ps.setInt(1, i);
                    ps.setString(2, "Angajat " + i);
                    ps.setDouble(3, 5000.00);
                    ps.setInt(4, 1);
                    ps.executeUpdate();

                    if (i % 100 == 0) {
                        conn.commit();
                    }
                }
                conn.commit();
            } catch (SQLException e) {
                conn.rollback();
                throw e;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        long elapsed = System.currentTimeMillis() - start;
        System.out.println("[COMMIT IN BATCHES] Elapsed time: " + elapsed + " ms");
        return elapsed;
    }

    private long oneTimeCommit() {
        long start = System.currentTimeMillis();
        try (Connection conn = getConnection()) {
            conn.setAutoCommit(false);
            String sql = "INSERT INTO employees (id, name, salary, department_id) VALUES (?, ?, ?, ?)";

            try (PreparedStatement ps = conn.prepareStatement(sql)) {
                for (int i = 1; i <= 5000; i++) {
                    ps.setInt(1, i);
                    ps.setString(2, "Angajat " + i);
                    ps.setDouble(3, 5000.00);
                    ps.setInt(4, 1);
                    ps.addBatch();
                    if (i % 50 == 0) {
                        ps.executeBatch();
                    }
                }
                ps.executeBatch();
                conn.commit();
            } catch (SQLException e) {
                conn.rollback();
                throw e;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        long elapsed = System.currentTimeMillis() - start;
        System.out.println("[ONE-TIME COMMIT] Elapsed time: " + elapsed + " ms");
        return elapsed;
    }

    private void printResults(long[] a, long[] b, long[] c) {
        System.out.println("\n╔══════════════════════════════════════════════════════╗");
        System.out.println("║           BATCH INSERT RESULTS                       ║");
        System.out.println("╠══════════════╦═════════════╦═════════════╦═══════════╣");
        System.out.printf("║ %-12s ║ %-11s ║ %-11s ║ %-9s ║%n",
                "Rulare", "Auto-commit", "Commit/100", "Batch");
        System.out.println("╠══════════════╬═════════════╬═════════════╬═══════════╣");

        for (int i = 0; i < 3; i++) {
            System.out.printf("║ Rulare %-5d ║ %8d ms ║ %8d ms ║ %6d ms ║%n",
                    (i + 1), a[i], b[i], c[i]);
        }

        long avgA = (long) Arrays.stream(a).average().orElse(0.0);
        long avgB = (long) Arrays.stream(b).average().orElse(0.0);
        long avgC = (long) Arrays.stream(c).average().orElse(0.0);

        System.out.println("╠══════════════╬═════════════╬═════════════╬═══════════╣");
        System.out.printf("║ %-12s ║ %8d ms ║ %8d ms ║ %6d ms ║%n",
                "MEDIE", avgA, avgB, avgC);
        System.out.println("╚══════════════╩═════════════╩═════════════╩═══════════╝");
    }
}
