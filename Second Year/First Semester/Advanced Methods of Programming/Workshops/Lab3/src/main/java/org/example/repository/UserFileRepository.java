package org.example.repository;

import org.example.domain.Duck;
import org.example.domain.DuckType;
import org.example.domain.Person;
import org.example.domain.User;

import java.time.LocalDate;
import java.util.List;

/**
 * Repository for storing {@link User} entities in a file.
 * Supports both {@link Person} and {@link Duck} types.
 * Extends {@link AbstractFileRepository} and implements
 * conversion between file lines and entity objects.
 */
public class UserFileRepository extends AbstractFileRepository<Long, User> {

    /**
     * Constructs a new UserFileRepository with the given file name.
     *
     * @param fileName the name of the file where users are stored
     */
    public UserFileRepository(String fileName) {
        super(fileName);
    }

    /**
     * Converts a list of strings (read from a file line) into a {@link User} entity.
     * The first element of the list indicates the user type ("Person" or "Duck").
     *
     * @param data the list of string values representing the user's fields
     * @return the {@link User} created from the list of strings
     * @throws IllegalArgumentException if the user type is invalid or unrecognized
     */
    @Override
    public User extractEntity(List<String> data) {
        Long id = Long.parseLong(data.get(0));
        String userType = data.get(1);
        String username = data.get(2);
        String email = data.get(3);
        String password = data.get(4);
        if (userType.equals("Person")) {
            String surname = data.get(5);
            String name = data.get(6);
            LocalDate birthDate = LocalDate.parse(data.get(7));
            String occupation = data.get(8);
            return new Person(id, userType, username, email, password, surname, name, birthDate, occupation);
        } else if (userType.equals("Duck")) {
            DuckType duckType = DuckType.valueOf(data.get(5));
            Double speed = Double.parseDouble(data.get(6));
            Double resistance = Double.parseDouble(data.get(7));
            return new Duck(id, userType, username, email, password, duckType, speed, resistance);
        } else {
            throw new IllegalArgumentException("Invalid user type: " + userType);
        }
    }

    /**
     * Converts a {@link User} entity into a string suitable for storing in a file.
     * Supports both {@link Person} and {@link Duck} types.
     *
     * @param entity the {@link User} entity to convert
     * @return the string representation of the user for file storage
     * @throws IllegalArgumentException if the user type is invalid or unrecognized
     */
    @Override
    protected String createEntityAsString(User entity) {
        String id = entity.getId().toString();
        String userType = entity.getUserType();
        String username = entity.getUsername();
        String email = entity.getEmail();
        String password = entity.getPassword();
        if (userType.equals("Person")) {
            Person person = (Person) entity;
            String surname = person.getSurname();
            String name = person.getName();
            String birthdate = person.getBirthdate().toString();
            String occupation = person.getOccupation();
            return id + ';' + userType + ';' + username + ';' + email + ';' + password + ';' + surname + ';' + name + ';' + birthdate + ';' + occupation;
        } else if (userType.equals("Duck")) {
            Duck duck = (Duck) entity;
            String duckType = duck.getDuckType().toString();
            String speed = duck.getSpeed().toString();
            String resistance = duck.getResistance().toString();
            return id + ';' + userType + ';' + username + ';' + email + ';' + password + ';' + duckType + ';' + speed + ';' + resistance;
        } else {
            throw new IllegalArgumentException("Invalid user type: " + userType);
        }
    }
}
