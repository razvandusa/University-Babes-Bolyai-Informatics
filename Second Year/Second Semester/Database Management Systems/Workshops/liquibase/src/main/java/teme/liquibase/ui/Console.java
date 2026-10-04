package teme.liquibase.ui;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;
import teme.liquibase.OptimisticLockDemo;
import teme.liquibase.service.EmployeeService;

import java.util.Scanner;

@Component
@RequiredArgsConstructor
public class Console {
    private final OptimisticLockDemo optimisticLockDemo;
    private final EmployeeService employeeService;

    private void showMenu() {
        System.out.println("1. Optimistic Lock Demo");
        System.out.println("2. Soft Delete Employee");
        System.out.println("3. [ADMIN] Show Deleted Employees");
        System.out.println("4. Restore Deleted Employee");
        System.out.println("5. [ADMIN] Delete Employee Permanently");
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            showMenu();
            System.out.print("Enter your choice: ");
            String userInput = scanner.nextLine().trim();
            switch (userInput) {
                case "1":
                    optimisticLockDemo.simulateConflict();
                    break;
                case "2":
                    System.out.print("Enter the ID of the employee to delete: ");
                    String employeeId = scanner.nextLine().trim();
                    employeeService.softDeleteEmployee(Integer.valueOf(employeeId), "user");
                    break;
                case "3":
                    employeeService.showDeletedEmployees();
                    break;
                case "4":
                    System.out.print("Enter the ID of the employee to restore: ");
                    String employeeToBeRestoredId = scanner.nextLine().trim();
                    employeeService.restoreEmployee(Integer.valueOf(employeeToBeRestoredId));
                    break;
                case "5":
                    System.out.println("Enter the ID of the employee to delete permanently: ");
                    String employeeIdToDelete = scanner.nextLine().trim();
                    employeeService.hardDeleteEmployee(Integer.valueOf(employeeIdToDelete));
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}
