package org.example.repo;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import org.example.domain.Course;

public class CourseDBRepository {
    private final EntityManagerFactory emf;

    public CourseDBRepository() {
        this.emf = JPAUtil.getEntityManagerFactory();
    }

    /**
     * Check if a course exists in the database
     * @param id Course ID
     * @return True if course exists, false otherwise
     */
    public Boolean existsCourse(int id) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.find(Course.class, id) != null;
        } catch (Exception e) {
            System.out.println("Error checking if course exists in database: " + e.getMessage());
            return false;
        }
    }

    public Course getCourse(int id) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.find(Course.class, id);
        } catch (Exception e) {
            System.out.println("Error getting course from database: " + e.getMessage());
            return null;
        }
    }
}
