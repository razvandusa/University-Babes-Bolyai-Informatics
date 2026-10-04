package teme.liquibase.repository;

import jakarta.transaction.Transactional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import teme.liquibase.domain.Employee;

import java.util.List;
import java.util.Optional;

@Repository
public interface EmployeeDBRepository extends JpaRepository<Employee, Integer> {
    @Query(value = "SELECT * FROM employees WHERE email = :email", nativeQuery = true)
    List<Employee> findByEmail(String email);

    @Query(value = "SELECT * FROM employees WHERE department_id = :departmentId", nativeQuery = true)
    List<Employee> findByDepartmentId(Integer departmentId);

    @Query(value = "SELECT * FROM employees WHERE id = :id", nativeQuery = true)
    Optional<Employee> findByIdIncludingDeleted(Integer id);

    @Query(value = "SELECT * FROM employees WHERE is_deleted = true", nativeQuery = true)
    List<Employee> findDeletedEmployees();

    @Modifying(clearAutomatically = true)
    @Transactional
    @Query(value = "UPDATE employees SET is_deleted = false, deleted_at = null, deleted_by = null WHERE id = :id",
            nativeQuery = true)
    void restoreEmployee(Integer id);
}
