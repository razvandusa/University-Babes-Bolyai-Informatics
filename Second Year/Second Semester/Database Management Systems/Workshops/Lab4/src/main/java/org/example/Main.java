package org.example;

import org.example.domain.Department;
import org.example.domain.Employee;
import org.example.repository.DepartmentDBRepository;
import org.example.repository.EmployeeDBRepository;
import org.example.service.Service;

import java.math.BigDecimal;

public class Main {
    public static void main(String[] args) {
        DepartmentDBRepository departmentRepository = new DepartmentDBRepository();
        EmployeeDBRepository employeeRepository = new EmployeeDBRepository();
        Service service = new Service(departmentRepository, employeeRepository);

//        service.demonstrateNPlusOne();

//        service.solveNPlusOne();

//        service.searchByEmail();

//        service.searchByDepartment();

//        service.searchBySalaryInterval();

//        service.searchByDepartmentAndSalaryGreaterThan();

//        service.updateSalaryIndividually(1);

//        service.updateSalaryInMass(1);

//        service.updateSalaryInBatches(1);

//        service.uncachedPreparedStatement();

//        service.cachedPreparedStatement();
    }
}
