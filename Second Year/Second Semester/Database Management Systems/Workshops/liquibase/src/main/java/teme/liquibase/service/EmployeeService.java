package teme.liquibase.service;
import jakarta.persistence.EntityNotFoundException;
import org.springframework.orm.ObjectOptimisticLockingFailureException;
import org.springframework.stereotype.Service;
import teme.liquibase.domain.Department;
import teme.liquibase.domain.Employee;
import teme.liquibase.repository.DepartmentDBRepository;
import teme.liquibase.repository.EmployeeDBRepository;
import lombok.extern.slf4j.Slf4j;

import java.math.BigDecimal;
import java.util.List;
import java.util.Optional;

@Service
@Slf4j
public class EmployeeService {
    private final EmployeeDBRepository employeeRepository;
    private final DepartmentDBRepository departmentRepository;

    public EmployeeService(EmployeeDBRepository employeeDBRepository, DepartmentDBRepository departmentRepository) {
        this.employeeRepository = employeeDBRepository;
        this.departmentRepository = departmentRepository;
    }

    public void add10000Employees() {
        Optional<Department> dep = departmentRepository.findById(1);
        Department d = dep.get();

        System.out.println("Începe inserarea a 10.000 de angajați...");

        for (int i = 1; i <= 10000; i++) {
            Employee emp = new Employee();

            emp.setName("Employee " + i);

            emp.setEmail("employee" + i + "@gmail.com");

            double randomSalary = 3000.0 + (Math.random() * 5000.0);
            emp.setSalary(BigDecimal.valueOf(randomSalary));

            emp.setDepartment(d);

            String phone = "07" + (int) (Math.random() * 90000000) + (int) (Math.random() * 9000000);
            emp.setPhone(phone);

            employeeRepository.save(emp);

            if (i % 1000 == 0) {
                System.out.println("Am procesat " + i + " înregistrări...");
            }
        }
        System.out.println("Inserare finalizată cu succes!");
    }

    public void searchByEmail() {
        System.out.println("Start searching by email...");
        double average = 0;
        for (int i = 1; i <= 100; i++) {
            long startTime = System.currentTimeMillis();

            String email = "employee95458@gmail.com";
            List<Employee> employees = employeeRepository.findByEmail(email);
            if (employees.isEmpty()) {
                System.out.println("No employees found with email: " + email);
            } else {
                System.out.println(employees.size() + " employees found with email: " + email);
            }

            long endTime = System.currentTimeMillis();
            System.out.println("Timp curent: " + (endTime - startTime) + " ms");
            if (i > 1) {
                average += (endTime - startTime);
            }
        }
        average /= 99;
        System.out.println("Timp mediu: " + average + " ms");
    }

    public void searchByDepartment() {
        System.out.println("Start searching by department...");
        double average = 0;
        for (int i = 1; i <= 100; i++) {
            long startTime = System.currentTimeMillis();

            Integer departmentId = 3;
            List<Employee> employees = employeeRepository.findByDepartmentId(departmentId);
            if (employees.isEmpty()) {
                System.out.println("No employees found in department with id: " + departmentId);
            } else {
                System.out.println(employees.size() + " employees found in department with id: " + departmentId);
            }

            long endTime = System.currentTimeMillis();
            System.out.println("Timp curent: " + (endTime - startTime) + " ms");
            if (i > 1) {
                average += (endTime - startTime);
            }
        }
        average /= 99;
        System.out.println("Timp mediu: " + average + " ms");
    }

    public Employee getEmployeeById(Integer employeeId) {
        return employeeRepository.findById(employeeId).orElse(null);
    }

    public Employee updateSalary(Integer employeeId, BigDecimal newSalary) {
        try {
            Employee employee = employeeRepository
                    .findById(employeeId)
                    .orElseThrow(() -> new EntityNotFoundException("Employee not found"));
            employee.setSalary(newSalary);
            return employeeRepository.save(employee);
        }
        catch (ObjectOptimisticLockingFailureException ex) {
            //logging pentru debugging
            log.error("Optimistic locking conflict detected for employee id {}", employeeId);
            log.error("Conflict details: ", ex);
            throw ex;
        }
    }

    public void softDeleteEmployee(Integer employeeId, String username) {
        Employee employee = employeeRepository
                .findById(employeeId)
                .orElseThrow(() -> new EntityNotFoundException("Employee not found"));
        employee.softDelete(username);
        employeeRepository.save(employee);
        System.out.println("""
            EMPLOYEE SOFT DELETED
            Deleted by: """
                + username);
    }

    public void restoreEmployee(Integer employeeId) {
        employeeRepository.restoreEmployee(employeeId);
        System.out.println("""
            EMPLOYEE RESTORED
            """);
    }

    public void showDeletedEmployees() {
        List<Employee> deletedEmployees = employeeRepository.findDeletedEmployees();
        System.out.println("""
            ===== DELETED EMPLOYEES =====
            """);
        deletedEmployees.forEach(employee -> {
            System.out.println("""
                ID: """ + employee.getId());
            System.out.println("Name: " + employee.getName());
            System.out.println("Deleted by: " + employee.getDeletedBy());
            System.out.println("Deleted at: " + employee.getDeletedAt());
            System.out.println("------------------");
        });
    }

    public void hardDeleteEmployee(Integer employeeId) {
        employeeRepository.deleteById(employeeId);
        System.out.println("""
            HARD DELETE EXECUTED
            Employee permanently removed.
            """);
    }
}
