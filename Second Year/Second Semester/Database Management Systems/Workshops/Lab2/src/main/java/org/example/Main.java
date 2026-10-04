package org.example;


import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Properties props = new Properties();
        try {
            props.load(new FileReader("bd.config"));
        } catch (IOException e) {
            System.out.println("Eroare la citirea fisierului de configurare.");
            e.printStackTrace();
            return;
        }

        DirtyRead dr = new DirtyRead(props);
        NonRepeatableRead nrr = new NonRepeatableRead(props);
        PhantomRead pr = new PhantomRead(props);
        LostUpdate lu = new LostUpdate(props);
        Deadlock d = new Deadlock(props);
        BatchInsert bi = new BatchInsert(props);

        while (true) {
            System.out.println("1. Dirty Read");
            System.out.println("2. Non-Repeatable Read");
            System.out.println("3. Phantom Read");
            System.out.println("4. Lost Update");
            System.out.println("5. Deadlock");
            System.out.println("6. Batch Insert Performance");
            System.out.println("0. Iesire");
            System.out.print("Alege o optiune: ");
            String input = scanner.nextLine().trim();

            switch (input) {
                case "1" -> dr.run();
                case "2" -> nrr.run();
                case "3" -> pr.run();
                case "4" -> lu.run();
                case "5" -> d.run();
                case "6" -> bi.run();
                case "0" -> {
                    System.out.println("Iesire...");
                    scanner.close();
                    return;
                }
                default -> System.out.println("Nu e o optiune valida.");
            }
        }
    }
}