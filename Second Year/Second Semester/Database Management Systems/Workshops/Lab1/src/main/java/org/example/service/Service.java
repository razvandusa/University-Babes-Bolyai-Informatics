package org.example.service;

import org.example.domain.Course;
import org.example.domain.Enrollment;
import org.example.domain.Student;
import org.example.repo.CourseDBRepository;
import org.example.repo.DatabaseManager;
import org.example.repo.EnrollmentDBRepository;
import org.example.repo.StudentDBRepository;

import java.util.List;

public class Service {
    private StudentDBRepository studentRepo;
    private EnrollmentDBRepository enrollmentRepo;
    private CourseDBRepository courseRepo;

    public Service(StudentDBRepository studentRepo, EnrollmentDBRepository enrollmentRepo, CourseDBRepository courseRepo) {
        this.studentRepo = studentRepo;
        this.enrollmentRepo = enrollmentRepo;
        this.courseRepo = courseRepo;
    }

    public List<Student> getAllStudents() {
        return studentRepo.getAllStudents();
    }

    public List<Enrollment> getEnrollmentsByStudentId(int studentId) {
        return enrollmentRepo.getEnrollmentsByStudentId(studentId);
    }

    public void addEnrollment(Enrollment enrollment) {
        //add enrollment only if course exists and enrollment does not exist
        if (!courseRepo.existsCourse(enrollment.getCourse().getId())) {
            throw new RuntimeException("Course does not exist");
        }
        if (enrollmentRepo.existsEnrollment(enrollment))
            throw new RuntimeException("Enrollment already exists");
        enrollmentRepo.addEnrollment(enrollment);
    }

    public void updateEnrollment(Enrollment selectedEnrollment, Enrollment newEnrollment) {
        //delete old enrollment and add new enrollment
        //new enrollment must have valid student and course ids
        if (!studentRepo.existsStudent(newEnrollment.getStudent().getId())) {
            throw new RuntimeException("Student does not exist");
        }
        if (!courseRepo.existsCourse(newEnrollment.getCourse().getId())) {
            throw new RuntimeException("Course does not exist");
        }
        enrollmentRepo.deleteEnrollment(selectedEnrollment);
        enrollmentRepo.addEnrollment(newEnrollment);
    }

    public void deleteEnrollment(Enrollment enrollment) {
        enrollmentRepo.deleteEnrollment(enrollment);
    }

    public List<Enrollment> getAllEnrollments() {
        return enrollmentRepo.getAllEnrollments();
    }

    public Course getCourseById(int id) {
        return courseRepo.getCourse(id);
    }

    public Student getStudentById(int id) {
        return studentRepo.getStudent(id);
    }
}
