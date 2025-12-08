package org.example.validation;

import org.example.domain.Friendship;
import org.example.exceptions.validationExceptions.friendshipExceptions.SameIdException;

/**
 * Validator implementation for {@link Friendship} entities.
 * Ensures that friendship-related constraints are respected.
 */
public class FriendshipValidationStrategy implements ValidationStrategy<Friendship> {
    /**
     * Validates the given friendship.
     *
     * @param friendship the friendship entity to be validated
     * @throws RuntimeException if validation fails
     */
    @Override
    public void validate(Friendship friendship) {
        Long idFirstFriend = friendship.getFirstFriendId();
        Long idSecondFriend = friendship.getSecondFriendId();

        validateDifferentId(idFirstFriend, idSecondFriend);
    }

    private void validateDifferentId(Long idFirstFriend, Long idSecondFriend) {
        if (idFirstFriend.equals(idSecondFriend)) {
            throw new SameIdException("A user cannot be friends with themselves");
        }
    }
}
