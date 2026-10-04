package org.example.repo;

import jakarta.persistence.EntityManager;
import jakarta.persistence.EntityManagerFactory;
import org.example.domain.Enrollment;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class EnrollmentDBRepository {
    private final EntityManagerFactory emf;

    public EnrollmentDBRepository() {
        this.emf = JPAUtil.getEntityManagerFactory();
    }

    /**
     * Get all enrollments for a given student
     * @param studentId Student ID
     * @return List of enrollments
     */
    public List<Enrollment> getEnrollmentsByStudentId(int studentId) {
        try (EntityManager em = emf.createEntityManager()) {
            return em.createQuery("""
            SELECT e FROM Enrollment e
            WHERE e.student.id = :studentId
        """, Enrollment.class)
                    .setParameter("studentId", studentId)
                    .getResultList();
        } catch (Exception e) {
            System.out.println("Error getting enrollments for given student from database: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }

    /**
     * Add an enrollment to the database
     * @param enrollment Enrollment to add
     */
    public void addEnrollment(Enrollment enrollment) {
        try (EntityManager em = emf.createEntityManager()) {
            em.getTransaction().begin();
            em.persist(enrollment);
            em.getTransaction().commit();
        } catch (Exception e) {
            System.out.println("Error adding enrollment to database: " + e.getMessage());
            throw new RuntimeException(e);
        }
    }

    /**
     * Delete an enrollment from the database
     * @param enrollment Enrollment to delete
     */
    public void deleteEnrollment(Enrollment enrollment) {
        EntityManager em = emf.createEntityManager();
        try {
            em.getTransaction().begin();

            Enrollment managedEnrollment = em.find(Enrollment.class, enrollment.getId());
            if (managedEnrollment != null) {
                em.remove(managedEnrollment);
            }

            em.getTransaction().commit();
        } catch (Exception e) {
            if (em.getTransaction().isActive()) {
                em.getTransaction().rollback();
            }
            System.out.println("Error deleting enrollment from database: " + e.getMessage());
            throw new RuntimeException(e);
        } finally {
            em.close();
        }
    }

    /**
     * Check if an enrollment exists in the database
     * @param enrollment Enrollment to check
     * @return True if enrollment exists, false otherwise
     */
    public Boolean existsEnrollment(Enrollment enrollment) {
        try (EntityManager em = emf.createEntityManager()) {
            Long count = em.createQuery("""
            SELECT COUNT(e) FROM Enrollment e
            WHERE e.student.id = :studentId
            AND e.course.id = :courseId
        """, Long.class)
                    .setParameter("studentId", enrollment.getStudent().getId())
                    .setParameter("courseId", enrollment.getCourse().getId())
                    .getSingleResult();

            return count > 0;
        } catch (Exception e) {
            System.out.println("Error checking if enrollment exists in database: " + e.getMessage());
            return false;
        }
    }

    /**
     * Get all enrollments from the database
     * @return List of enrollments
     */
    public List<Enrollment> getAllEnrollments() {
        try (EntityManager em = emf.createEntityManager()) {
            return em.createQuery("SELECT s FROM Enrollment s", Enrollment.class)
                     .getResultList();
        } catch (Exception e) {
            System.out.println("Error getting all enrollments from database: " + e.getMessage());
            return new ArrayList<>();
        }
    }
}
