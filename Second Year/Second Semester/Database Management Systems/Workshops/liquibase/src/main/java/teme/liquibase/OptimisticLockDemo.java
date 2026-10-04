package teme.liquibase;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.orm.ObjectOptimisticLockingFailureException;
import org.springframework.stereotype.Component;
import teme.liquibase.domain.Employee;
import teme.liquibase.repository.EmployeeDBRepository;

import java.math.BigDecimal;
import java.util.Scanner;

@Component
@RequiredArgsConstructor
@Slf4j
public class OptimisticLockDemo {
    private final EmployeeDBRepository employeeRepository;

    public void simulateConflict() {
        try {
            System.out.println("\n========== START DEMO ==========\n");

            //user A citeste employee
            Employee userAEmployee = employeeRepository.findById(1).orElseThrow();

            //user B citeste acelasi employee
            Employee userBEmployee = employeeRepository.findById(1).orElseThrow();

            System.out.println("User A loaded version: " + userAEmployee.getVersion());
            System.out.println("User B loaded version: " + userBEmployee.getVersion());

            //user A modifica si salveaza
            userAEmployee.setSalary(BigDecimal.valueOf(7000.0));
            employeeRepository.save(userAEmployee);
            System.out.println("""
                    User A updated salary successfully.
                    New version is now:
                    """
                    + userAEmployee.getVersion());

            //user B modifica folosind versiune veche
            userBEmployee.setSalary(BigDecimal.valueOf(9000.0));
            employeeRepository.save(userBEmployee);
        }
        catch (ObjectOptimisticLockingFailureException ex) {
            //logging pentru debugging
            log.error("""
                    OPTIMISTIC LOCK CONFLICT DETECTED

                    Another user modified the entity
                    before the current transaction completed.
                    """);

            log.error("Detailed error:", ex);

            System.out.println("""
                    ====================================
                    CONFLICT DETECTED
                    ====================================

                    Another user modified this employee
                    before your update was saved.

                    OPTIONS:
                    1. Reload latest data
                    2. Force update
                    3. Cancel operation

                    ====================================
                    """);

            Scanner scanner = new Scanner(System.in);
            System.out.print("Enter your choice: ");
            String userInput = scanner.nextLine().trim();

            if (userInput.equals("1")) {
                //reload latest data
                Employee latestEmployee = employeeRepository.findById(1).orElseThrow();

                System.out.println("""
                    Latest database state:
                    
                    Salary: """
                        + latestEmployee.getSalary()
                        + "\nVersion: "
                        + latestEmployee.getVersion());
            }
            else if (userInput.equals("2")) {
                //force update
                Employee latestEmployee = employeeRepository.findById(1).orElseThrow();
                latestEmployee.setSalary(BigDecimal.valueOf(9000.0));
                employeeRepository.save(latestEmployee);

                System.out.println("""
                    Force update completed.
                    New salary: """
                        + latestEmployee.getSalary());
            }
            else if (userInput.equals("3")) {
                //cancel operation
                System.out.println("""
                    Operation cancelled.
                    """);
            }
            else {
                System.out.println("Invalid choice");
            }
        }
    }
}