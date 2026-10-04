package org.example.repository;
import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import jakarta.persistence.EntityTransaction;
import jakarta.persistence.Query;
import org.example.domain.Employee;
import org.springframework.stereotype.Repository;

import java.math.BigDecimal;
import java.util.List;

@Repository
public class EmployeeDBRepository {
    private EntityManagerFactory emf;

    public EmployeeDBRepository() {
        this.emf = JPAUtils.getEntityManagerFactory();
    }

    public void save(Employee employee) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            em.persist(employee);
            tx.commit();
        } catch (Exception e) {
            if (tx != null && tx.isActive())
                tx.rollback();
            e.printStackTrace();
        } finally {
            em.close();
        }
    }

    public List<Employee> findByEmail(String email) {
        EntityManager em = emf.createEntityManager();
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e WHERE e.email = :email", Employee.class)
                .setParameter("email", email)
                .getResultList();
        return employees;
    }

    public List<Employee> findByDepartment(Integer departmentId) {
        EntityManager em = emf.createEntityManager();
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e WHERE e.department.id = :departmentId", Employee.class)
                .setParameter("departmentId", departmentId)
                .getResultList();
        return employees;
    }

    public List<Employee> findBySalaryInterval(Double minSalary, Double maxSalary) {
        EntityManager em = emf.createEntityManager();
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e WHERE e.salary BETWEEN :minSalary AND :maxSalary", Employee.class)
                .setParameter("minSalary", minSalary)
                .setParameter("maxSalary", maxSalary)
                .getResultList();
        return employees;
    }

    public List<Employee> findByDepartmentAndSalaryGreaterThan(Integer departmentId, Double salary) {
        EntityManager em = emf.createEntityManager();
        List<Employee> employees = em.createQuery("SELECT e FROM Employee e WHERE e.department.id = :departmentId AND e.salary > :salary", Employee.class)
                .setParameter("departmentId", departmentId)
                .setParameter("salary", salary)
                .getResultList();
        return employees;
    }

    public void updateSalaryIndividually(Integer deptId) {
        EntityManager em = emf.createEntityManager();
        List<Employee> employees = findByDepartment(deptId);
        for (Employee emp : employees) {
            emp.setSalary(emp.getSalary().multiply(BigDecimal.valueOf(1.1)));
            em.merge(emp);
        }
    }

    public void updateSalaryInMass(Integer deptId) {
        EntityManager em = emf.createEntityManager();
        em.getTransaction().begin();

        String sql = "UPDATE Employee e SET e.salary = e.salary * 1.1 WHERE e.department.id = :deptId";
        em.createQuery(sql)
                .setParameter("deptId", deptId)
                .executeUpdate();

        em.getTransaction().commit();
        em.close();
    }

    public void updateSalaryInBatches(Integer deptId) {
        EntityManager em = emf.createEntityManager();
        EntityTransaction tx = em.getTransaction();
        try {
            tx.begin();
            List<Employee> employees = findByDepartment(deptId);

            int batchSize = 50;
            for (int i = 0; i < employees.size(); i++) {
                Employee emp = employees.get(i);
                BigDecimal newSalary = emp.getSalary().multiply(BigDecimal.valueOf(1.1));
                emp.setSalary(newSalary);
                em.merge(emp);

                if ((i + 1) % batchSize == 0) {
                    em.flush();
                    em.clear();
                }
            }
            tx.commit();
        } catch (Exception e) {
            if (tx != null && tx.isActive())
                tx.rollback();
            throw e;
        } finally {
            em.close();
        }
    }

    public void uncachedPreparedStatements() {
        EntityManager em = emf.createEntityManager();
        for (int i = 1; i <= 1000; i++) {
            Query query = em.createQuery("SELECT e FROM Employee e WHERE e.id = :id");
            query.setParameter("id", (long) i);
            query.getSingleResult();
        }
    }

    public void cachedPreparedStatements() {
        EntityManager em = emf.createEntityManager();
        Query query = em.createQuery("SELECT e FROM Employee e WHERE e.id = :id");
        for (int i = 1; i <= 1000; i++) {
            query.setParameter("id", (long) i);
            query.getSingleResult();
        }
    }
}
