package org.example.ui;

import org.example.domain.Friendship;
import org.example.domain.User;
import org.example.service.FriendshipService;
import org.example.service.UserService;

import java.util.List;
import java.util.Scanner;

/**
 * Console-based user interface for interacting with the social network application.
 * Provides menu-driven operations for managing users, friendships, and social network analytics.
 */
public class Console {
    private final UserService userService;
    private final FriendshipService friendshipService;

    public Console(UserService userService, FriendshipService friendshipService) {
        this.userService = userService;
        this.friendshipService = friendshipService;
    }

    /**
     * Displays the main menu of the application.
     */
    public void menu() {
        System.out.println("===== MENU =====");
        System.out.println("1. Add User");
        System.out.println("2. Remove User");
        System.out.println("3. List Users");
        System.out.println("4. Add Friendship");
        System.out.println("5. Remove Friendship");
        System.out.println("6. List Friendships");
        System.out.println("7. Show The Number Of Communities");
        System.out.println("8. Show The Most Sociable Community");
        System.out.println("0. Exit");
        System.out.println("================");
        System.out.print("Choose an option: ");
    }

    /**
     * Starts the interactive console loop, allowing the user to select menu options
     * and perform corresponding actions.
     */
    public void run() {
        boolean run = true;
        Scanner scanner = new Scanner(System.in);
        while (run) {
            menu();
            String choice = scanner.nextLine();
            switch (choice) {
                case "1":
                    addUser();
                    break;
                case "2":
                    removeUser();
                    break;
                case "3":
                    listUsers();
                    break;
                case "4":
                    addFriendship();
                    break;
                case "5":
                    removeFriendship();
                    break;
                case "6":
                    listFriendships();
                    break;
                case "7":
                    showNumberOfCommunities();
                    break;
                case "8":
                    showTheMostSociableCommunity();
                    break;
                case "0":
                    run = false;
                    System.out.println("Exiting...");
                    break;
                default:
                    System.out.println("Invalid option, please try again.");
            }
        }
    }

    /**
     * Prompts the user to input information and adds a new Person or Duck.
     * All exceptions are caught and printed to the console.
     */
    public void addUser() {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Select user type:");
        System.out.println("1. Person");
        System.out.println("2. Duck");
        System.out.print("Choose an option: ");

        String choice = scanner.nextLine();

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        System.out.print("Enter surname: ");
        String surname = scanner.nextLine();

        switch (choice) {
            case "1":
                System.out.print("Enter name: ");
                String name = scanner.nextLine();

                System.out.print("Enter birthdate (yyyy-MM-dd): ");
                String birthdate = scanner.nextLine();

                System.out.print("Enter occupation: ");
                String occupation = scanner.nextLine();

                try {
                    userService.add("Person", username, email, password, surname, name, birthdate, occupation);
                    System.out.println("Person added successfully!");
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
                break;
            case "2":
                System.out.print("Enter duck type: ");
                String duckType = scanner.nextLine();

                System.out.print("Enter duck speed: ");
                String duckSpeed = scanner.nextLine();

                System.out.print("Enter duck resistance: ");
                String duckResistance = scanner.nextLine();

                try {
                    userService.add("Duck", username, email, password, duckType, duckSpeed, duckResistance);
                    System.out.println("Duck added successfully!");
                } catch (Exception e) {
                    System.out.println(e.getMessage());
                }
                break;
            default:
                System.out.println("Invalid option");
        }
    }

    /**
     * Prompts the user for a user ID and removes the corresponding user
     * and all their friendships.
     * All exceptions are caught and printed to the console.
     */
    public void removeUser() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the ID of the user you want to remove: ");
        String id = scanner.nextLine();

        try {
            userService.remove(id);
            friendshipService.removeAllFriendshipsOfUser(id);
            System.out.println("User removed successfully!");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Displays all users in the system.
     */
    public void listUsers() {
        System.out.print("========== All users ==========\n");
        Iterable<User> users = userService.findAll();
        for (User user : users) {
            System.out.println(user);
        }
        System.out.println("===============================");
    }

    /**
     * Prompts for two user IDs and creates a friendship between them.
     * All exceptions are caught and printed to the console.
     */
    public void addFriendship() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the ID of the first user: ");
        String firstId = scanner.nextLine();

        System.out.print("Enter the ID of the second user: ");
        String secondId = scanner.nextLine();

        try {
            friendshipService.add(firstId, secondId);
            System.out.println("Friendship added successfully!");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Prompts for a friendship ID and removes the corresponding friendship.
     * All exceptions are caught and printed to the console.
     */
    public void removeFriendship() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the ID of the friendship you want to remove: ");
        String id = scanner.nextLine();

        try {
            friendshipService.remove(id);
            System.out.println("Friendship removed successfully!");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    /**
     * Displays all friendships in the system.
     */
    public void listFriendships() {
        System.out.print("======== All friendships ========\n");
        Iterable<Friendship> friendships = friendshipService.findAll();
        for (Friendship friendship : friendships) {
            System.out.println(friendship);
        }
        System.out.println("===============================");
    }

    /**
     * Displays the number of communities in the social network.
     */
    public void showNumberOfCommunities() {
        int numberOfCommunities = friendshipService.getNumberOfCommunities();
        System.out.println("The number of communities is: " + numberOfCommunities);
    }

    /**
     * Displays the most sociable community, i.e., the community with the largest diameter.
     * If there is no such community, prints a message accordingly.
     */
    public void showTheMostSociableCommunity() {
        List<Long> mostSociableCommunity = friendshipService.getMostSociableCommunity();
        if (mostSociableCommunity.isEmpty()) {
            System.out.println("There is no sociable community");
            return;
        }

        System.out.println("The most sociable community contains the following users: ");

        for (Long userId : mostSociableCommunity) {
            User user = userService.findById(userId.toString());
            System.out.println(user);
        }
    }
}
