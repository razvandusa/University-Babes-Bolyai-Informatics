package org.example.domain;

import java.time.LocalDate;

/**
 * Represents a person in the social network.
 * A person has a surname, first name, birthdate, and occupation,
 * in addition to the inherited User fields (id, username, email, password).
 */
public class Person extends User {
    private String surname;
    private String name;
    private LocalDate birthDate;
    private String occupation;

    /**
     * Constructs a new Person with the specified details.
     *
     * @param id the unique identifier inherited from User
     * @param username the username of the person
     * @param email the email of the person
     * @param password the password of the person
     * @param surname the surname (last name) of the person
     * @param name the first name of the person
     * @param birthDate the birthdate of the person
     * @param occupation the occupation of the person
     */
    public Person(Long id, String userType, String username, String email, String password, String surname, String name, LocalDate birthDate, String occupation) {
        super(id, userType, username, email, password);
        this.surname = surname;
        this.name = name;
        this.birthDate = birthDate;
        this.occupation = occupation;
    }

    public String getSurname() { return surname; }
    public String getName() { return name; }
    public LocalDate getBirthdate() { return birthDate; }
    public String getOccupation() { return occupation; }

    public void setSurname(String surname) { this.surname = surname; }
    public void setName(String name) { this.name = name; }
    public void setBirthdate(LocalDate birthDate) { this.birthDate = birthDate; }
    public void setOccupation(String occupation) { this.occupation = occupation; }

    @Override
    public String toString() {
        return "Person{" +
                super.toString() +
                ", surname='" + surname + '\'' +
                ", name='" + name + '\'' +
                ", birthDate=" + birthDate +
                ", occupation='" + occupation + '\'' +
                '}';
    }
}