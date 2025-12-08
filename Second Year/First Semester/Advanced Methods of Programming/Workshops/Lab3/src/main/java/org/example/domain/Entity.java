package org.example.domain;

import java.io.Serial;
import java.io.Serializable;
import java.util.Objects;

/**
 * Represents a generic entity with a unique identifier.
 * This class implements Serializable, allowing instances to be persisted or transmitted.
 *
 * @param <ID> the type of the unique identifier
 */
public class Entity<ID> implements Serializable {
    /** Unique identifier for the class version, used by Java to verify compatibility during serialization */
    @Serial
    private static final long serialVersionUID = 7331115341259248461L;
    private ID id;

    public ID getId() { return id; }
    public void setId(ID id) { this.id = id; }

    @Override
    public String toString() {
        return "Entity{" +
                "id=" + id + '}';
    }

    /**
     * Compares this entity to another object for equality.
     * Two entities are considered equal if they are of the same class and have the same unique identifier (id).
     *
     * @param o the reference object with which to compare
     * @return true if the entities are equal, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Entity<?> entity = (Entity<?>) o;
        return Objects.equals(id, entity.id);
    }

    /**
     * Returns the hash code value for the entity.
     * The hash code is computed based on the unique identifier (id) to be consistent with equals().
     *
     * @return the hash code of the entity
     */
    @Override
    public int hashCode() {
        return Objects.hash(getId());
    }
}
