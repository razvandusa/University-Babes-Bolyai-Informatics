package org.example.domain;

import java.util.Objects;

/**
 * Represents a friendship relationship between two users.
 * The friendship is considered unidirectional, so the friendship between user A and user B is identical to a
 * friendship between user B and user A.
 */
public class Friendship extends Entity<Long> {
    private Long firstFriendId;
    private Long secondFriendId;

    /**
     * Constructs a new Friendship between two users.
     *
     * @param id the unique identifier of the friendship entity
     * @param firstFriendId the ID of the first user
     * @param secondFriendId the ID of the second user
     */
    public Friendship(Long id, Long firstFriendId, Long secondFriendId) {
        super.setId(id);
        this.firstFriendId = firstFriendId;
        this.secondFriendId = secondFriendId;
    }

    public Long getFirstFriendId() { return firstFriendId; }
    public Long getSecondFriendId() { return secondFriendId; }

    public void setFirstFriendId(Long id) { this.firstFriendId = id; }
    public void setSecondFriendId(Long id) { this.secondFriendId = id; }

    @Override
    public String toString() {
        return "Friendship{" +
                "id=" + getId() +
                ", firstUserId=" + firstFriendId +
                ", secondUserId=" + secondFriendId +
                '}';
    }

    /**
     * Compares two Friendship objects for equality.
     * Two friendships are considered equal if they contain the same pair of the user IDs, regardless of their order.
     *
     * @param o the reference object with which to compare
     * @return true if the friendship represent the same relationship, false otherwise
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Friendship other = (Friendship) o;
        return (Objects.equals(firstFriendId, other.firstFriendId) && Objects.equals(secondFriendId, other.secondFriendId))
            || (Objects.equals(firstFriendId, other.secondFriendId) && Objects.equals(secondFriendId, other.firstFriendId));
    }

    /**
     * Returns a hash code value for this friendship.
     * The order of user IDs does not affect the resulting hash code.
     *
     * @return the hash code of the friendship
     */
    @Override
    public int hashCode() {
        return Objects.hash(firstFriendId.hashCode() + secondFriendId.hashCode());
    }
}
