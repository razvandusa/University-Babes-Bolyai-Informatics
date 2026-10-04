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

    @Autowired
    private CacheManager cacheManager;

    public Service(DepartmentDBRepository departmentRepository, EmployeeDBRepository employeeRepository) {
        this.departmentRepository = departmentRepository;
        this.employeeRepository = employeeRepository;
    }

    public void demonstrateNPlusOne() {
        EntityManager em = emf.createEntityManager();
        System.out.println("--- Start Demonstrare N+1 ---");
        long startTime = System.currentTimeMillis();

        List<Department> departments = em
                .createQuery("SELECT d FROM Department d", Department.class)
                .getResultList();

        for (Department department : departments) {
            List<Employee> employees = department.getEmployees();
            System.out.println(department.getName() + " are " + employees.size() + " angajati");
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Timp execuție: " + (endTime - startTime) + " ms");
    }

    public void solveNPlusOne() {
        EntityManager em = emf.createEntityManager();
        System.out.println("--- Start Solve N+1 ---");
        long startTime = System.currentTimeMillis();

        List<Department> departments = em
                .createQuery("SELECT DISTINCT d FROM Department d LEFT JOIN FETCH d.employees", Department.class)
                .getResultList();

        for (Department department : departments) {
            List<Employee> employees = department.getEmployees();
            System.out.println(department.getName() + " are " + employees.size() + " angajati");
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Timp execuție: " + (endTime - startTime) + " ms");
    }

    public void add10000Employees() {
        Department d = departmentRepository.findById(1);

        System.out.println("Începe inserarea a 10.000 de angajați...");

        for (int i = 1; i <= 10000; i++) {
            Employee emp = new Employee();
            emp.setEmail("employee" + i + "@gmail.com");

            double randomSalary = 3000.0 + (Math.random() * 5000.0);
            emp.setSalary(BigDecimal.valueOf(randomSalary));

            emp.setDepartment(d);

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

            List<Employee> employees = employeeRepository.findByDepartment(7);
            System.out.println(employees.size() + " employees found in department with id: 7");

            long endTime = System.currentTimeMillis();
            if (i > 1) {
                average += (endTime - startTime);
            }
        }
        average /= 99;
        System.out.println("Timp mediu: " + average + " ms");
    }

    public void searchBySalaryInterval() {
        System.out.println("Start searching by salary interval...");
        double average = 0;
        for (int i = 1; i <= 100; i++) {
            long startTime = System.currentTimeMillis();

            List<Employee> employees = employeeRepository.findBySalaryInterval(4000.0, 6000.0);
            System.out.println(employees.size() + " employees found in salary interval: 4000.0 - 6000.0");

            long endTime = System.currentTimeMillis();
            if (i > 1) {
                average += (endTime - startTime);
            }
        }
        average /= 99;
        System.out.println("Timp mediu: " + average + " ms");
    }

    public void searchByDepartmentAndSalaryGreaterThan() {
        System.out.println("Start searching by department and salary greater than...");
        double average = 0;
        for (int i = 1; i <= 100; i++) {
            long startTime = System.currentTimeMillis();

            List<Employee> employees = employeeRepository.findByDepartmentAndSalaryGreaterThan(6, 6000.0);
            System.out.println(employees.size() + " employees found in department with id: 6 and salary greater than: 6000.0");

            long endTime = System.currentTimeMillis();
            if (i > 1) {
                average += (endTime - startTime);
            }
        }
        average /= 99;
        System.out.println("Timp mediu: " + average + " ms");
    }

    public List<Employee> getEmployeesByOffset(int pageNumber, int pageSize) {
        EntityManager em = emf.createEntityManager();
        return em.createQuery("SELECT e FROM Employee e ORDER BY e.id", Employee.class)
                .setFirstResult((pageNumber - 1) * pageSize)
                .setMaxResults(pageSize)
                .getResultList();
    }

    public List<Employee> getEmployeesByKeyset(Long lastId, int pageSize) {
        EntityManager em = emf.createEntityManager();
        return em.createQuery("SELECT e FROM Employee e WHERE e.id > :lastId ORDER BY e.id", Employee.class)
                .setParameter("lastId", lastId == null ? 0 : lastId)
                .setMaxResults(pageSize)
                .getResultList();
    }

    public int getEmployeeCount() {
        EntityManager em = emf.createEntityManager();
        return em.createQuery("SELECT COUNT(e) FROM Employee e", Long.class).getSingleResult().intValue();
    }

    @Cacheable(value = "departments", key = "#id")
    public Department getDepartmentById(Integer id) {
        System.out.println("Cache MISS pentru ID: " + id + ". Accesăm baza de date...");
        return departmentRepository.findById(id);
    }

    @CacheEvict(value = "departments", key = "#id")
    public void updateDepartment(Integer id, String newName) {
        Department dept = departmentRepository.findById(id);
        if (dept != null) {
            dept.setName(newName);
            departmentRepository.update(dept);
            System.out.println("Cache INVALIDAT pentru ID: " + id);
        }
    }

    public String getCacheStatistics() {
        CaffeineCache caffeineCache = (CaffeineCache) cacheManager.getCache("departments");
        var stats = caffeineCache.getNativeCache().stats();

        return String.format(
                "Cache Stats - Hits: %d, Misses: %d, Hit Rate: %.2f%%",
                stats.hitCount(),
                stats.missCount(),
                stats.hitRate() * 100
        );
    }

    public void updateSalaryIndividually(Integer deptId) {
        System.out.println("Start updating salary individually for department ID: " + deptId + "...");
        long startTime = System.currentTimeMillis();
        employeeRepository.updateSalaryIndividually(deptId);
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " ms");
    }

    public void updateSalaryInMass(Integer deptId) {
        System.out.println("Start updating salary in mass for department ID: " + deptId + "...");
        long startTime = System.currentTimeMillis();
        employeeRepository.updateSalaryInMass(deptId);
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " ms");
    }

    public void updateSalaryInBatches(Integer deptId) {
        System.out.println("Start updating salary in batches for department ID: " + deptId + "...");
        long startTime = System.currentTimeMillis();
        employeeRepository.updateSalaryInBatches(deptId);
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " ms");
    }

    public void uncachedPreparedStatement() {
        System.out.println("Start uncached prepared statement...");
        long startTime = System.currentTimeMillis();
        employeeRepository.uncachedPreparedStatements();
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " ms");
    }

    public void cachedPreparedStatement() {
        System.out.println("Start cached prepared statement...");
        long startTime = System.currentTimeMillis();
        employeeRepository.cachedPreparedStatements();
        long endTime = System.currentTimeMillis();
        System.out.println("Time: " + (endTime - startTime) + " ms");
    }
}
