package org.example;

import java.sql.*;
import java.util.Properties;

public class PhantomRead {
    private String url;
    private String user;
    private String pass;

    public PhantomRead(Properties props) {
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
            stmt.execute("INSERT INTO employees (id, name, salary, department_id) VALUES (1, 'John', 5000, 5);");
            stmt.execute("INSERT INTO employees (id, name, salary, department_id) VALUES (2, 'Jane', 5500, 5);");
        }
    }

    public void run() {
        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        phantomRead();

        System.out.println();
        System.out.println("---------------------------");
        System.out.println();

        try {
            setup();
        } catch (SQLException e) {
            e.printStackTrace();
            return;
        }

        phantomReadSolved();
//        runWithSolution();
    }

    private void phantomRead() {
        Object lock1 = new Object();
        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                conn.setTransactionIsolation(Connection.TRANSACTION_READ_COMMITTED);
                System.out.println("[A] BEGIN TRANSACTION");

                PreparedStatement ps = conn.prepareStatement("SELECT COUNT(*) FROM employees WHERE department_id = 5;");

                ResultSet rs1 = ps.executeQuery();
                if (rs1.next()) {
                    System.out.println("[A] (First count) Numar de angajati din departamentul 5: " + rs1.getInt(1));
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
                    System.out.println("[A] (Second count) Numar de angajati din departamentul 5: " + rs2.getInt(1) + " <-- PHANTOM READ!");
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

               PreparedStatement ps = conn.prepareStatement("INSERT INTO employees (id, name, salary, department_id) VALUES (3, 'Bob', 5000, 5);");
               ps.executeUpdate();
               conn.commit();

               System.out.println("[B] Insert new employee in dept. 5 and commit!");

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

    private void phantomReadSolved() {
//        Object lock1 = new Object();
//        Object lock2 = new Object();

        Thread transA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                conn.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
                System.out.println("[A] BEGIN TRANSACTION (SERIALIZABLE)");

                PreparedStatement ps = conn.prepareStatement("SELECT COUNT(*) FROM employees WHERE department_id = 5;");

                ResultSet rs1 = ps.executeQuery();
                if (rs1.next()) {
                    System.out.println("[A] (First count) Numar de angajati din departamentul 5: " + rs1.getInt(1));
                }

//                synchronized (lock1) {
//                    lock1.notifyAll();
//                }
//                synchronized (lock2) {
//                    try {
//                        lock2.wait(8000);
//                    } catch (InterruptedException e) {}
//                }

                ResultSet rs2 = ps.executeQuery();
                if (rs2.next()) {
                    System.out.println("[A] (Second count) Numar de angajati din departamentul 5: " + rs2.getInt(1) + " <-- acelasi numar ca in primul SELECT!");
                }

                conn.commit();
                System.out.println("[A] COMMIT");

            } catch (SQLException e) {
                e.printStackTrace();
            }
        });

        Thread transB = new Thread(() -> {
//            synchronized (lock1) {
//                try {
//                    lock1.wait(3000);
//                } catch (InterruptedException e) {
//                    e.printStackTrace();
//                }
//            }
            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] BEGIN TRANSACTION");

                PreparedStatement ps = conn.prepareStatement("INSERT INTO employees (id, name, salary, department_id) VALUES (3, 'Bob', 5000, 5);");
                ps.executeUpdate();
                conn.commit();

                System.out.println("[B] Insert new employee in dept. 5 and commit!");

            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
//                synchronized (lock2) {
//                    lock2.notifyAll();
//                }
            }
        });

        transA.start();
        try {
            transA.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        transB.start();
        try {
            transA.join();
            transB.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void runWithSolution() {
        Object lockAfterFirstCount = new Object();
        Object lockAfterBInsert = new Object();

        Thread transactionA = new Thread(() -> {
            try (Connection conn = getConnection()) {
                conn.setTransactionIsolation(Connection.TRANSACTION_SERIALIZABLE);
                conn.setAutoCommit(false);
                System.out.println("[A] Pornesc tranzactia (SERIALIZABLE)");

                PreparedStatement count = conn.prepareStatement(
                        "SELECT COUNT(*) AS cnt FROM employees WHERE department_id = 5");

                ResultSet rs1 = count.executeQuery();
                if (rs1.next())
                    System.out.println("[A] Prima numarare: " + rs1.getInt("cnt") + " angajati in dept 5");

                synchronized (lockAfterFirstCount) { lockAfterFirstCount.notifyAll(); }
                synchronized (lockAfterBInsert) {
                    try { lockAfterBInsert.wait(5000); } catch (InterruptedException ignored) {}
                }

                ResultSet rs2 = count.executeQuery();
                if (rs2.next())
                    System.out.println("[A] A doua numarare: " + rs2.getInt("cnt")
                            + " angajati in dept 5 <-- aceeasi valoare, SERIALIZABLE isi face treaba");

                conn.commit();
                System.out.println("[A] Commit");

            } catch (SQLException e) {
                System.out.println("[A] Eroare: " + e.getMessage());
            }
        });

        Thread transactionB = new Thread(() -> {
            synchronized (lockAfterFirstCount) {
                try { lockAfterFirstCount.wait(3000); } catch (InterruptedException ignored) {}
            }

            try (Connection conn = getConnection()) {
                conn.setAutoCommit(false);
                System.out.println("[B] Pornesc tranzactia, incerc INSERT");

                PreparedStatement insert = conn.prepareStatement(
                        "INSERT INTO employees (id, name, salary, department_id) VALUES (?, ?, ?)");
                insert.setString(1, "Angajat Nou Serializable");
                insert.setDouble(2, 3000.00);
                insert.setInt(3, 5);
                insert.executeUpdate();
                conn.commit();
                System.out.println("[B] INSERT facut dupa ce A a terminat");

            } catch (SQLException e) {
                System.out.println("[B] Blocat/eroare (normal cu SERIALIZABLE): " + e.getMessage());
            } finally {
                synchronized (lockAfterBInsert) { lockAfterBInsert.notifyAll(); }
            }
        });

        transactionA.start();
        transactionB.start();
        try { transactionA.join(); transactionB.join(); } catch (InterruptedException ignored) {}
    }
}
