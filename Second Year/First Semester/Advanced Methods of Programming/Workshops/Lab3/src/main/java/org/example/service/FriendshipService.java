package org.example.service;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.exceptions.EntityAlreadyExists;
import org.example.exceptions.EntityNotFoundException;
import org.example.exceptions.validationExceptions.userExceptions.IdValidationException;
import org.example.repository.Repository;
import org.example.validation.ValidationStrategy;
import org.example.validation.ValidatorContext;

import java.util.*;

/**
 * Service layer for managing {@link Friendship} entities.
 */
public class FriendshipService extends AbstractService<Long, Friendship> {
    private final Repository<Long, User> userRepository;
    private final ValidatorContext<Friendship> validatorFriendship;

    public FriendshipService(Repository<Long, Friendship> friendshipRepository, Repository<Long, User> userRepository, ValidatorContext<Friendship> validatorFriendship) {
        super(friendshipRepository);
        this.userRepository = userRepository;
        this.validatorFriendship = validatorFriendship;
    }

    /**
     * Adds a new friendship between two users.
     *
     * @param fields the ids of the two users to be friends
     * @throws IdValidationException if the ids are not valid numbers
     * @throws EntityNotFoundException if any of the users do not exist
     * @throws EntityAlreadyExists if the friendship already exists
     */
    @Override
    public void add(String... fields) {
        String idFirstFriend = fields[0];
        String idSecondFriend = fields[1];
        long longIdFirstFriend;
        long longIdSecondFriend;
        try {
            longIdFirstFriend = Long.parseLong(idFirstFriend);
            longIdSecondFriend = Long.parseLong(idSecondFriend);
        } catch (NumberFormatException e) {
            throw new IdValidationException("The id must be a number");
        }

        Friendship friendship = new Friendship(generateID(), longIdFirstFriend, longIdSecondFriend);
        validatorFriendship.validate(friendship);
        if (userRepository.findById(longIdFirstFriend) == null) {
            throw new EntityNotFoundException("The user with id " + idFirstFriend + " was not found");
        } else if (userRepository.findById(longIdSecondFriend) == null) {
            throw new EntityNotFoundException("The user with id " + idSecondFriend + " was not found");
        }
        if (existsFriendship(idFirstFriend, idSecondFriend)) {
            throw new EntityAlreadyExists("The friendship between " + idFirstFriend + " and " + idSecondFriend + " already exists");
        }
        repository.add(new Friendship(generateID(), longIdFirstFriend, longIdSecondFriend));
    }

    /**
     * Removes a friendship by its id.
     *
     * @param id the id of the friendship to remove
     * @throws IdValidationException if the id is not a valid number
     * @throws EntityNotFoundException if the friendship does not exist
     */
    @Override
    public void remove(String id) {
        long longId;
        try {
            longId = Long.parseLong(id);
        } catch (NumberFormatException e) {
            throw new IdValidationException("The id must be a number");
        }
        if (repository.findById(longId) == null) {
            throw new EntityNotFoundException("The friendship with id " + id + " was not found");
        }
        repository.remove(repository.findById(longId));
    }

    /**
     * Generates a new unique id for a friendship.
     *
     * @return a new unique id
     */
    @Override
    public Long generateID() {
        long maxNumber = 0;
        for (Friendship friendship : super.findAll()) {
            if (friendship.getId() > maxNumber) {
                maxNumber = friendship.getId();
            }
        }
        return maxNumber + 1;
    }

    /**
     * Checks if a friendship exists between two users.
     *
     * @param idFirstFriend the id of the first user
     * @param idSecondFriend the id of the second user
     * @return true if the friendship exists, false otherwise
     * @throws IdValidationException if any id is not a valid number
     */
    public boolean existsFriendship(String idFirstFriend, String idSecondFriend) {
        long longIdFirstFriend;
        long longIdSecondFriend;
        try {
            longIdFirstFriend = Long.parseLong(idFirstFriend);
        } catch (NumberFormatException e) {
            throw new IdValidationException(e.getMessage());
        }
        try {
            longIdSecondFriend = Long.parseLong(idSecondFriend);
        } catch (NumberFormatException e) {
            throw new IdValidationException(e.getMessage());
        }
        for (Friendship friendship : repository.findAll()) {
            if (friendship.getFirstFriendId().equals(longIdFirstFriend) && friendship.getSecondFriendId().equals(longIdSecondFriend) ||
                    friendship.getFirstFriendId().equals(longIdSecondFriend)  && friendship.getSecondFriendId().equals(longIdFirstFriend)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Removes all friendships of a user given the user's id.
     *
     * @param id the id of the user whose friendships are to be removed
     * @throws IdValidationException if the id is not a valid number
     */
    public void removeAllFriendshipsOfUser(String id) {
        long longId;
        try {
            longId = Long.parseLong(id);
        } catch (NumberFormatException e) {
            throw new IdValidationException("The id must be a number");
        }
        List<Friendship> toRemove = new ArrayList<>();
        for (Friendship friendship : repository.findAll()) {
            if (friendship.getFirstFriendId().equals(longId) || friendship.getSecondFriendId().equals(longId)) {
                toRemove.add(friendship);
            }
        }
        for (Friendship friendship : toRemove) {
            repository.remove(friendship);
        }
    }

    /**
     * Returns the number of communities (connected groups of users) with at least two members.
     *
     * @return the number of communities
     */
    public int getNumberOfCommunities() {
        Map<Long, List<Long>> graph = buildGraph();
        Set<Long> visited = new HashSet<>();

        int numberOfCommunities = 0;

        for (Long userId : graph.keySet()) {
            if (!visited.contains(userId) && !graph.get(userId).isEmpty()) {
                int size = dfsSize(userId, graph, visited);
                if (size >= 2) numberOfCommunities++;
            }
        }

        return numberOfCommunities;
    }

    private Map<Long, List<Long>> buildGraph() {
        Map<Long, List<Long>> graph = new HashMap<>();
        for (User user : userRepository.findAll()) graph.put(user.getId(), new ArrayList<>());
        for (Friendship f : repository.findAll()) {
            graph.get(f.getFirstFriendId()).add(f.getSecondFriendId());
            graph.get(f.getSecondFriendId()).add(f.getFirstFriendId());
        }
        return graph;
    }

    private int dfsSize(Long nodeId, Map<Long, List<Long>> graph, Set<Long> visited) {
        visited.add(nodeId);
        int size = 1;
        for (Long neighbor : graph.get(nodeId)) {
            if (!visited.contains(neighbor)) {
                size += dfsSize(neighbor, graph, visited);
            }
        }
        return size;
    }

    /**
     * Returns the most sociable community (the connected component with the largest diameter).
     *
     * @return the list of user ids in the most sociable community
     */
    public List<Long> getMostSociableCommunity() {
        Map<Long , List<Long>> graph = buildGraph();
        Set<Long> visited = new HashSet<>();
        int maxDiameter = -1;
        List<Long> mostSociableCommunity = new ArrayList<>();

        for (Long userId : graph.keySet()) {
            if (!visited.contains(userId) && !graph.get(userId).isEmpty()) {
                List<Long> component = new ArrayList<>();
                dfsCollect(userId, graph, visited, component);

                int diameter = getCommunityDiameter(component, graph);

                if (diameter > maxDiameter) {
                    maxDiameter = diameter;
                    mostSociableCommunity = component;
                }
            }
        }

        return mostSociableCommunity;
    }

    private void dfsCollect(Long nodeId, Map<Long, List<Long>> graph, Set<Long> visited, List<Long> component) {
        visited.add(nodeId);
        component.add(nodeId);
        for (Long neighbor : graph.get(nodeId)) {
            if (!visited.contains(neighbor)) {
                dfsCollect(neighbor, graph, visited, component);
            }
        }
    }

    private Long bfsFarthestNode(Long start, Map<Long, List<Long>> graph, List<Long> component) {
        Queue<Long> queue = new LinkedList<>();
        Set<Long> visited = new HashSet<>();
        queue.add(start);
        visited.add(start);
        Long farthest = start;

        while (!queue.isEmpty()) {
            Long current = queue.poll();
            farthest = current;
            for (Long neighbor : graph.get(current)) {
                if (component.contains(neighbor) && !visited.contains(neighbor)) {
                    visited.add(neighbor);
                    queue.add(neighbor);
                }
            }
        }
        return farthest;
    }

    private int bfsMaxDistance(Long start, Map<Long, List<Long>> graph, List<Long> component) {
        Queue<Long> queue = new LinkedList<>();
        Map<Long, Integer> distance = new HashMap<>();
        queue.add(start);
        distance.put(start, 0);
        int maxDistance = 0;

        while (!queue.isEmpty()) {
            Long current = queue.poll();
            int currentDistance = distance.get(current);
            maxDistance = Math.max(currentDistance, maxDistance);

            for (Long neighbor : graph.get(current)) {
                if (component.contains(neighbor) && !distance.containsKey(neighbor)) {
                    distance.put(neighbor, currentDistance + 1);
                    queue.add(neighbor);
                }
            }
        }

        return maxDistance;
    }

    private int getCommunityDiameter(List<Long> component, Map<Long, List<Long>> graph) {
        if (component.isEmpty()) return 0;
        Long start = component.getFirst();
        Long farthest = bfsFarthestNode(start, graph, component);
        return bfsMaxDistance(farthest, graph, component);
    }

}
