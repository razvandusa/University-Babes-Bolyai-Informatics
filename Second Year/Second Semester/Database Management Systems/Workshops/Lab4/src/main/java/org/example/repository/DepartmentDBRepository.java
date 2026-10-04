package org.example.repository;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import org.example.domain.Department;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.stereotype.Repository;
import org.springframework.cache.annotation.Cacheable;


@Repository
public class DepartmentDBRepository {
    private EntityManagerFactory emf;

    public DepartmentDBRepository() {
        this.emf = JPAUtils.getEntityManagerFactory();
    }

    //@Cacheable("departments")
    public Department findById(Integer id) {
        EntityManager em = emf.createEntityManager();
        Department department = em.find(Department.class, id);
        em.close();
        return department;
    }

    //@CacheEvict(value = "departments", key = "#department.id")
    public void update(Department department) {
        EntityManager em = emf.createEntityManager();
        em.merge(department);
        em.close();
    }
}