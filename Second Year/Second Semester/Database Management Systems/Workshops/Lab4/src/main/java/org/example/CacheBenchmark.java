package org.example;

import org.example.repository.DepartmentDBRepository;
import org.example.repository.EmployeeDBRepository;
import org.example.service.Service;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

@Component
public class CacheBenchmark implements CommandLineRunner {
    @Autowired
    private Service service;

    @Override
    public void run(String... args) throws Exception {
        System.out.println("\n=== START TEST CACHE ===");
        Integer testId = 1;

        // 1. Primul apel (Miss)
        service.getDepartmentById(testId);

        // 2. Al doilea apel (Hit)
        long start = System.currentTimeMillis();
        service.getDepartmentById(testId);
        System.out.println("Timp HIT: " + (System.currentTimeMillis() - start) + " ms");

        // 3. DEMONSTRAȚIE EVICȚIUNE (Manuală prin Update)
        service.updateDepartment(testId, "Departament Nou");
        start = System.currentTimeMillis();
        service.getDepartmentById(testId); // Va fi MISS pentru că am dat Evict
        System.out.println("Timp după EVICT (trebuie să fie mare): " + (System.currentTimeMillis() - start) + " ms");

        // 4. DEMONSTRAȚIE EXPIRARE TTL (Automată prin timp)
        System.out.println("Așteptăm 6 secunde pentru expirare TTL...");
        service.getDepartmentById(testId); // Acum e în cache (Hit)
        Thread.sleep(6000); // Așteptăm să expire (TTL e 5s)

        start = System.currentTimeMillis();
        service.getDepartmentById(testId); // Va fi MISS din cauza expirării
        System.out.println("Timp după EXPIRARE TTL: " + (System.currentTimeMillis() - start) + " ms");

        System.out.println("Statistici finale: " + service.getCacheStatistics());
        System.out.println("=== SFÂRȘIT TEST ===\n");
    }
}
