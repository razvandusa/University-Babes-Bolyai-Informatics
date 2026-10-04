package org.example.service;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.Query;
import org.example.domain.Department;
import org.example.domain.Employee;
import org.example.repository.DepartmentDBRepository;
import org.example.repository.EmployeeDBRepository;
import org.example.repository.JPAUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.CacheManager;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.cache.caffeine.CaffeineCache;

import java.math.BigDecimal;
import java.util.List;

@org.springframework.stereotype.Service
public class Service {
    private EntityManagerFactory emf = JPAUtils.getEntityManagerFactory();

    @Autowired
    private DepartmentDBRepository departmentRepository;

    @Autowired
    private EmployeeDBRepository employeeRepository;

    public Service(DepartmentDBRepository departmentRepository, EmployeeDBRepository employeeRepository) {
        this.departmentRepository = departmentRepository;
        this.employeeRepository = employeeRepository;
    }
}
