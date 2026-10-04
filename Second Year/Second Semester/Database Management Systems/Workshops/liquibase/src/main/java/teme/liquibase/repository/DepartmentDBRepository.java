package teme.liquibase.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import teme.liquibase.domain.Department;

@Repository
public interface DepartmentDBRepository extends JpaRepository<Department, Integer> {

}
