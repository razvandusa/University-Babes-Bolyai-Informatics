package org.example;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.repository.FriendshipFileRepository;
import org.example.repository.Repository;
import org.example.repository.UserFileRepository;
import org.example.service.FriendshipService;
import org.example.service.UserService;
import org.example.ui.Console;
import org.example.validation.FriendshipValidationStrategy;
import org.example.validation.UserValidationStrategy;
import org.example.validation.ValidatorContext;

public class Main {
    static void main() {
        Repository<Long, User> userRepository = new UserFileRepository("/Users/razvandusa/IdeaProjects/SocialNetwork/src/main/java/org/example/ui/users.txt");
        Repository<Long, Friendship> friendshipRepository = new FriendshipFileRepository("/Users/razvandusa/IdeaProjects/SocialNetwork/src/main/java/org/example/ui/friendships.txt");

        ValidatorContext<User> userValidator = new ValidatorContext<>(new UserValidationStrategy());
        ValidatorContext<Friendship> friendshipValidator = new ValidatorContext<>(new FriendshipValidationStrategy());

        UserService userService = new UserService(userRepository, userValidator);
        FriendshipService friendshipService = new FriendshipService(friendshipRepository, userRepository, friendshipValidator);

        Console console = new Console(userService, friendshipService);

        console.run();
    }
}
