package org.example.service;

import org.example.domain.Duck;
import org.example.domain.DuckType;
import org.example.domain.Person;
import org.example.domain.User;
import org.example.exceptions.EntityNotFoundException;
import org.example.exceptions.validationExceptions.duckExceptions.DuckTypeValidationException;
import org.example.exceptions.validationExceptions.duckExceptions.ResistanceValidationException;
import org.example.exceptions.validationExceptions.duckExceptions.SpeedValidationException;
import org.example.exceptions.validationExceptions.personExceptions.BirthdateValidationException;
import org.example.exceptions.validationExceptions.userExceptions.IdValidationException;
import org.example.repository.Repository;
import org.example.validation.ValidationStrategy;
import org.example.validation.ValidatorContext;

import java.time.LocalDate;
import java.time.format.DateTimeParseException;
import java.util.Set;

/**
 * Service layer for managing {@link User}, {@link Duck}, and {@link Person} entities.
 */
public class UserService extends AbstractService<Long, User> {

    ValidatorContext<User> validatorUser;

    /**
     * Constructs a UserService with the given repository and validator.
     *
     * @param repository repository used to store users
     * @param validatorUser validator used to validate user entities
     */
    public UserService(Repository<Long, User> repository, ValidatorContext<User> validatorUser) {
        super(repository);
        this.validatorUser = validatorUser;
    }

    /**
     * Adds a new user of type Duck or Person with the given fields.
     *
     * @param fields a variable number of strings representing the entity data
     * @throws DuckTypeValidationException if the duck type is invalid
     * @throws SpeedValidationException if the speed is not a valid number
     * @throws ResistanceValidationException if the resistance is not a valid number
     * @throws BirthdateValidationException if the birthdate format is invalid
     */
    public void add(String ... fields) {
        String userType = fields[0];
        String username = fields[1];
        String email = fields[2];
        String password = fields[3];
        switch (userType) {
            case "Duck":
                String duckType = fields[4];
                String speed = fields[5];
                String resistance = fields[6];
                final Set<String> VALID_DUCK_TYPES = Set.of("FLYING", "SWIMMING", "FLYING_AND_SWIMMING");
                if (!VALID_DUCK_TYPES.contains(duckType)) {
                    throw new DuckTypeValidationException(
                            "Invalid duck type: " + duckType + ". Valid types are: " + VALID_DUCK_TYPES
                    );
                }
                double doubleSpeed;
                try {
                    doubleSpeed = Double.parseDouble(speed);
                } catch (NumberFormatException e) {
                    throw new SpeedValidationException("Speed must be a valid number");
                }
                double doubleResistance;
                try {
                    doubleResistance = Double.parseDouble(resistance);
                } catch (NumberFormatException e) {
                    throw new ResistanceValidationException("Resistance must be a valid number");
                }
                Duck duck = new Duck(generateID(),userType,username,email,password,DuckType.valueOf(duckType),doubleSpeed,doubleResistance);
                validatorUser.validate(duck);
                repository.add(duck);
                break;
            case "Person":
                LocalDate localDateBirthdate;
                String surname = fields[4];
                String name = fields[5];
                String birthdate = fields[6];
                String occupation = fields[7];
                try {
                    localDateBirthdate = LocalDate.parse(birthdate);
                }  catch (DateTimeParseException e) {
                    throw new BirthdateValidationException("Birthdate format must be yyyy-MM-dd");
                }
                Person person = new Person(generateID(), userType, username, email, password, surname, name, localDateBirthdate, occupation);
                validatorUser.validate(person);
                repository.add(person);
                break;
        }
    }

    /**
     * Removes a user by id
     *
     * @param id the identifier of the entity to be removed
     */
    @Override
    public void remove(String id) {
        long longId;
        try {
            longId = Long.parseLong(id);
        } catch (NumberFormatException e) {
            throw new IdValidationException("The id must be a number");
        }
        User user = repository.findById(longId);
        if (user == null) {
            throw new EntityNotFoundException("The user with id " + id + " was not found");
        }
        repository.remove(user);
    }

    /**
     * Generates a unique id for a new user.
     *
     * @return a new unique user id
     */
    @Override
    public Long generateID() {
        long maxNumber = 0;
        for (User user : super.findAll()) {
            if (user.getId() > maxNumber) {
                maxNumber = user.getId();
            }
        }
        return maxNumber + 1;
    }

    /**
     * Finds a user by id
     * @param id the id of the user to find
     * @return the User entity with the given id, or null if not found
     */
    public User findById(String id) {
        long longId;
        try {
            longId = Long.parseLong(id);
        } catch (NumberFormatException e) {
            throw new IdValidationException("The id must be a number");
        }
        return repository.findById(longId);
    }
}
