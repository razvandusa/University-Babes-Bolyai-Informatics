package org.example.repository;

import org.example.domain.Entity;

import java.io.*;
import java.util.Arrays;
import java.util.List;

/**
 * Abstract class representing a repository of entities stored in a file.
 * Provides basic functionality to load and save entities while keeping
 * them in memory via {@link InMemoryRepository}.
 *
 * @param <ID> the type of the identifier of the entity
 * @param <E>  the type of the entity, which extends {@link Entity}
 */
public abstract class AbstractFileRepository<ID, E extends Entity<ID>> extends InMemoryRepository<ID, E> {
    String fileName;

    /**
     * Constructs a new AbstractFileRepository with the specified file name.
     *
     * @param fileName the file name where entities will be loaded from and saved to
     */
    AbstractFileRepository(String fileName) {
        this.fileName = fileName;
        loadDataFromFile();
    }

    @Override
    public void add(E entity) {
        super.add(entity);
        writeToFile();
    }

    @Override
    public void remove(E entity) {
        super.remove(entity);
        writeToFile();
    }

    /**
     * Loads entities from the file into memory.
     * Each line in the file represents one entity.
     * Uses {@link #extractEntity(List)} to convert a line into an entity.
     */
    private void loadDataFromFile() {
        try (BufferedReader fileReader = new BufferedReader(new FileReader(fileName))) {
            String newLine;
            while ((newLine = fileReader.readLine()) != null) {
                /*
                  We need to use Arrays.asList because newLine.split returns an array of Strings, but we will use
                  a List<String> in extractEntity, which offers more useful methods.
                */
                List<String> data = Arrays.asList(newLine.split(";"));
                E entity = extractEntity(data);
                super.add(entity);
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Converts a list of strings (read from a file line) into an entity.
     * This method must be implemented by subclasses to create specific entity types.
     *
     * @param data the list of string values representing the entity's fields
     * @return the entity created from the list of strings
     */
    public abstract E extractEntity(List<String> data);

    /**
     * Converts an entity into a string representation suitable for writing to a file.
     * Each entity should be represented as a single line.
     *
     * @param entity the entity to convert
     * @return the string representation of the entity
     */
    protected abstract String createEntityAsString(E entity);

    /**
     * Writes all entities currently stored in memory to the file.
     * Each entity is converted to a string using {@link #createEntityAsString(Entity)}
     * and written as a single line in the file.
     */
    protected void writeToFile() {
        try (BufferedWriter fileWriter = new BufferedWriter(new FileWriter(fileName))) {
            for (E entity : findAll()) {
                fileWriter.write(createEntityAsString(entity));
                fileWriter.newLine();
            }
        } catch  (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
