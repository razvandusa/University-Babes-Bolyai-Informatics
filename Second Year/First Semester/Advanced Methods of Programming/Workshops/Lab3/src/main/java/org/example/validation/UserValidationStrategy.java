package org.example.validation;

import org.example.domain.Duck;
import org.example.domain.DuckType;
import org.example.domain.Person;
import org.example.domain.User;
import org.example.exceptions.validationExceptions.duckExceptions.ResistanceValidationException;
import org.example.exceptions.validationExceptions.duckExceptions.SpeedValidationException;
import org.example.exceptions.validationExceptions.personExceptions.BirthdateValidationException;
import org.example.exceptions.validationExceptions.personExceptions.NameException;
import org.example.exceptions.validationExceptions.personExceptions.SurnameException;
import org.example.exceptions.validationExceptions.userExceptions.EmailValidationException;
import org.example.exceptions.validationExceptions.userExceptions.PasswordValidationException;
import org.example.exceptions.validationExceptions.userExceptions.UserTypeValidationException;
import org.example.exceptions.validationExceptions.userExceptions.UsernameValidationException;

import java.time.LocalDate;
import java.util.Set;

/**
 * Validates {@link User} entities and their specific fields
 * depending on the concrete user type (Person or Duck).
 */
public class UserValidationStrategy implements ValidationStrategy<User> {

    private final Set<String> VALID_TYPES = Set.of("Person", "Duck");

    /**
     * Validates the given user.
     *
     * @param user the user to be validated
     * @throws RuntimeException if validation fails
     */
    @Override
    public void validate(User user) {
        String userType = user.getUserType();
        String username = user.getUsername();
        String email = user.getEmail();
        String password = user.getPassword();

        validateUserType(userType);
        validateUsername(username);
        validateEmail(email);
        validatePassword(password);

        if (user instanceof Person person) {
            String surname = person.getSurname();
            String name = person.getName();
            LocalDate birthdate = person.getBirthdate();
            String occupation = person.getOccupation();
            validatePersonFields(surname, name, birthdate, occupation);
        } else if (user instanceof Duck duck) {
            DuckType duckType = duck.getDuckType();
            Double speed = duck.getSpeed();
            Double resistance = duck.getResistance();
            validateDuckFields(duckType, speed, resistance);
        }
    }

    private void validateUserType(String userType) {
        if (!VALID_TYPES.contains(userType)) {
            throw new UserTypeValidationException(
                    "Invalid user type: " + userType + ". Valid types are: " + VALID_TYPES
            );
        }
    }

    private void validateUsername(String username) {
        if (username == null || username.isEmpty()) {
            throw new UsernameValidationException("Username cannot be empty");
        }

        if (username.length() < 3 || username.length() > 32) {
            throw new UsernameValidationException("Username length must be between 3 and 32 characters");
        }

        if (!username.matches("^[A-Za-z][A-Za-z0-9_]*$")) {
            throw new UsernameValidationException("Username must start with a letter and contain only letters, digits, or underscore");
        }
    }

    private void validateEmail(String email) {
        if (email == null || email.isEmpty()) {
            throw new EmailValidationException("Email cannot be empty");
        }

        if (!email.matches("^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$")) {
            throw new EmailValidationException("Invalid email format: " + email);
        }
    }

    private void validatePassword(String password) {
        if (password == null || password.isEmpty()) {
            throw new PasswordValidationException("Password cannot be empty");
        }

        if (password.length() < 8 || password.length() > 32) {
            throw new PasswordValidationException("Password length must be between 8 and 32 characters");
        }

        if (!password.matches("^[A-Za-z0-9_]+$")) {
            throw new PasswordValidationException("Password can contain only letters, digits, or underscore");
        }

        boolean hasLetter = password.matches(".*[A-Za-z].*");
        boolean hasDigit = password.matches(".*[0-9].*");

        if (!hasLetter || !hasDigit) {
            throw new PasswordValidationException("Password must contain at least one letter and one digit");
        }
    }

    private void validateDuckFields(DuckType duckType, Double speed, Double resistance) {
        validateSpeed(speed);
        validateResistance(resistance);
    }

    private void validateSpeed(Double speed) {
        if (speed == null) {
            throw new SpeedValidationException("Speed cannot be empty");
        }

        if (speed <= 0) {
            throw new SpeedValidationException("Speed must be a valid number");
        }
    }

    private void validateResistance(Double resistance) {
        if (resistance == null) {
            throw new ResistanceValidationException("Resistance cannot be empty");
        }

        if (resistance <= 0) {
            throw new ResistanceValidationException("Resistance must be greater than 0");
        }
    }

    private void validatePersonFields(String surname, String name, LocalDate birthdate, String occupation) {
        validateSurname(surname);
        validateName(name);
        validateBirthdate(birthdate);
        validateOccupation(occupation);
    }

    private void validateSurname(String surname) {
        if (surname == null || surname.isEmpty()) {
            throw new SurnameException("Surname cannot be empty");
        }

        if (surname.length() < 3 || surname.length() > 32) {
            throw new UsernameValidationException("Username length must be between 3 and 32 characters");
        }

        if (!surname.matches("^[A-Za-z]+$")) {
            throw new UsernameValidationException("Username must start with a letter and contain only letters");
        }
    }

    private void validateName(String name) {
        if (name == null || name.isEmpty()) {
            throw new NameException("Name cannot be empty");
        }

        if (name.length() < 3 || name.length() > 32) {
            throw new NameException("Name length must be between 3 and 32 characters");
        }

        if (!name.matches("^[A-Za-z]+$")) {
            throw new NameException("Name must start with a letter and contain only letters");
        }
    }

    private void validateBirthdate(LocalDate birthdate) {
        if (birthdate == null) {
            throw new BirthdateValidationException("Birthdate cannot be empty");
        }

        if (birthdate.isAfter(LocalDate.now())) {
            throw new BirthdateValidationException("Birthdate must not be in the future");
        }
    }

    private void validateOccupation(String occupation) {
        if (occupation == null || occupation.isEmpty()) {
            throw new RuntimeException("Occupation cannot be empty");
        }

        if (occupation.length() < 3 || occupation.length() > 64) {
            throw new RuntimeException("Occupation length must be between 3 and 64 characters");
        }

        if (!occupation.matches("^[A-Za-z0-9 ]+$")) {
            throw new RuntimeException("Occupation can contain only letters, digits and spaces");
        }
    }
}
