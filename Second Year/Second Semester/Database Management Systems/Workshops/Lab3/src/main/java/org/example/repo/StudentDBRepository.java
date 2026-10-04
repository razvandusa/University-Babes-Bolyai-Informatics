package org.example.repo;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import org.example.domain.Student;
import java.util.ArrayList;
import java.util.List;

public class StudentDBRepository {
    private EntityManagerFactory emf;

    public StudentDBRepository() {
        this.emf = JPAUtil.getEntityManagerFactory();
    }

    /**
     * Get all students from the database
     * @return List of students
     */
    public List<Student> getAllStudents() {
        try (EntityManager em = emf.createEntityManager()) {
            return em.createQuery("SELECT s FROM Student s", Student.class)
                     .getResultList();
        } catch (Exception e) {
            System.out.println("Error getting all students from database: " + e.getMessage());
            return new ArrayList<>();
        }
    }

    /**
     * Check if a student exists in the database
     * @param id Student ID
     * @return True if student exists, false otherwise
     */
    public Boolean existsStudent(int id) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.find(Student.class, id) != null;
        } catch (Exception e) {
            System.out.println("Error checking if student exists in database: " + e.getMessage());
            return false;
        }
    }

    public Student getStudent(int id) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.find(Student.class, id);
        } catch (Exception e) {
            System.out.println("Error getting student from database: " + e.getMessage());
            return null;
        }
    }
}
