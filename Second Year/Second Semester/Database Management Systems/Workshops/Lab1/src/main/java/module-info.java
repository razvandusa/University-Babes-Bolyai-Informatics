module Lab1.main {
    requires jakarta.persistence;
    requires java.sql;
    requires javafx.base;
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.graphics;
    requires org.hibernate.orm.core;
    requires com.zaxxer.hikari;
    opens org.example.domain to org.hibernate.orm.core;
}