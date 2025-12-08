package org.example.repository;

import org.example.domain.Duck;
import org.example.domain.Friendship;
import org.example.domain.Person;
import org.example.domain.User;


import java.util.List;

/**
 * Repository for storing {@link Friendship} entities in a file.
 * Extends {@link AbstractFileRepository} and implements
 * conversion between file lines and entity objects.
 */
public class FriendshipFileRepository extends AbstractFileRepository<Long, Friendship> {

    /**
     * Creates a file repository for friendships.
     *
     * @param fileName the name of the file where friendships are stored
     */
    public FriendshipFileRepository(String fileName) {
        super(fileName);
    }

    /**
     * Creates a {@link Friendship} entity from a list of string attributes
     * read from a file line.
     *
     * @param data a list of strings representing the friendship fields,
     *             in the following order:
     *             friendshipId, firstUserId, secondUserId
     * @return the {@link Friendship} created from the given data
     */
    @Override
    public Friendship extractEntity(List<String> data) {
        Long idFriendship = Long.parseLong(data.get(0));
        Long idFirstFriend = Long.parseLong(data.get(1));
        Long idSecondFriend = Long.parseLong(data.get(2));

        return new Friendship(idFriendship, idFirstFriend, idSecondFriend);
    }

    /**
     * Converts a {@link Friendship} entity into a string suitable for storing in a file.
     *
     * @param entity the {@link Friendship} entity to convert
     * @return the string representation of the user for file storage
     */
    @Override
    protected String createEntityAsString(Friendship entity) {
        Long idFriendship = entity.getId();
        Long idFirstFriend = entity.getFirstFriendId();
        Long idSecondFriend = entity.getSecondFriendId();

        return  idFriendship.toString() + ";" + idFirstFriend.toString() + ";" + idSecondFriend.toString();
    }
}
