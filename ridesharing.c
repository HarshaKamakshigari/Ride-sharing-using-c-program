#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_RIDES 100

// Define structures for User and Ride
typedef struct {
    char username[20];
    char password[20];
} User;

typedef struct {
    char from[20];
    char to[20];
    int distance;
    char driver[20];
    int status;  // 0: Requested, 1: Accepted, -1: Rejected
} Ride;

// Global arrays to store user and ride data
User users[MAX_USERS];
Ride rides[MAX_RIDES];
int userCount = 0;
int rideCount = 0;

// Function declarations
void registerUser();
void loginUser();
void requestRide();
void displayRides();
void acceptRide();
void displayUserRides(char username[]);
void completeRide();

int main() {
    int choice;

    do {
        printf("\n--- Ride-Sharing System ---\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. Request Ride\n");
        printf("4. Display Available Rides\n");
        printf("5. Accept Ride Request\n");
        printf("6. Display My Rides\n");
        printf("7. Complete Ride\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                requestRide();
                break;
            case 4:
                displayRides();
                break;
            case 5:
                acceptRide();
                break;
            case 6:
                if (userCount > 0) {
                    char username[20];
                    printf("Enter your username: ");
                    scanf("%s", username);
                    displayUserRides(username);
                } else {
                    printf("No registered users. Please register first.\n");
                }
                break;
            case 7:
                completeRide();
                break;
            case 8:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Function to register a new user
void registerUser() {
    if (userCount < MAX_USERS) {
        printf("Enter username: ");
        scanf("%s", users[userCount].username);
        printf("Enter password: ");
        scanf("%s", users[userCount].password);
        userCount++;
        printf("User registered successfully!\n");
    } else {
        printf("User limit reached. Cannot register more users.\n");
    }
}

// Function to login
void loginUser() {
    char username[20];
    char password[20];

    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter your password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful!\n");
            return;
        }
    }

    printf("Invalid username or password. Please try again.\n");
}

// Function to request a ride
void requestRide() {
    if (userCount == 0) {
        printf("No registered users. Please register first.\n");
        return;
    }

    if (rideCount < MAX_RIDES) {
        char from[20], to[20];
        int distance;

        printf("Enter your location: ");
        scanf("%s", from);
        printf("Enter destination: ");
        scanf("%s", to);
        printf("Enter estimated distance (in km): ");
        scanf("%d", &distance);

        // Store the ride request
        strcpy(rides[rideCount].from, from);
        strcpy(rides[rideCount].to, to);
        rides[rideCount].distance = distance;
        rides[rideCount].status = 0;  // Requested
        strcpy(rides[rideCount].driver, "N/A");
        rideCount++;

        printf("Ride requested successfully!\n");
    } else {
        printf("Ride limit reached. Cannot request more rides.\n");
    }
}

// Function to display available rides
void displayRides() {
    if (rideCount == 0) {
        printf("No available rides.\n");
    } else {
        printf("Available Rides:\n");
        for (int i = 0; i < rideCount; i++) {
            if (rides[i].status == 0) {
                printf("Ride %d: From %s to %s, Distance: %d km\n", i + 1, rides[i].from, rides[i].to, rides[i].distance);
            }
        }
    }
}

// Function to accept a ride request
void acceptRide() {
    if (rideCount == 0) {
        printf("No ride requests available.\n");
        return;
    }

    int rideIndex;
    printf("Enter the ride number you want to accept: ");
    scanf("%d", &rideIndex);

    if (rideIndex > 0 && rideIndex <= rideCount && rides[rideIndex - 1].status == 0) {
        char driver[20];
        printf("Enter your driver username: ");
        scanf("%s", driver);

        // Update the ride status and assign the driver
        rides[rideIndex - 1].status = 1;  // Accepted
        strcpy(rides[rideIndex - 1].driver, driver);

        printf("Ride accepted successfully!\n");
    } else {
        printf("Invalid ride selection or ride already accepted.\n");
    }
}

// Function to display rides for a specific user
void displayUserRides(char username[]) {
    printf("Your Rides:\n");
    for (int i = 0; i < rideCount; i++) {
        if (strcmp(rides[i].driver, username) == 0) {
            printf("Ride %d: From %s to %s, Distance: %d km, Status: %s\n", i + 1, rides[i].from, rides[i].to, rides[i].distance,
                   (rides[i].status == 1) ? "Accepted" : "Requested");
        }
    }
}

// Function to complete a ride
void completeRide() {
    if (rideCount == 0) {
        printf("No rides available.\n");
        return;
    }

    int rideIndex;
    printf("Enter the ride number you want to complete: ");
    scanf("%d", &rideIndex);

    if (rideIndex > 0 && rideIndex <= rideCount && rides[rideIndex - 1].status == 1) {
        // Mark the ride as completed
        rides[rideIndex - 1].status = -1;  // Rejected (completed)
        printf("Ride completed successfully!\n");
    } else {
        printf("Invalid ride selection or ride not yet accepted.\n");
    }
}