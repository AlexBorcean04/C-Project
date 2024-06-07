#include <iostream>
#include <fstream>
#include "Player.h"
#include "Team.h"
#include "Admin.h"

void displayAdminMenu() {
    std::cout << "1. Login\n";
    std::cout << "2. Create Admin\n";
    std::cout << "3. Exit\n";
    std::cout << "Select an option: ";
}

void displayMainMenu() {
    std::cout << "1. Add Player\n";
    std::cout << "2. Release Player\n";
    std::cout << "3. Start Match\n";
    std::cout << "4. Start Training\n";
    std::cout << "5. Substitute Player\n";
    std::cout << "6. Save Team Data\n";
    std::cout << "7. Load Team Data\n";
    std::cout << "8. Display Team\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    Team team;
    Admin admin(team);

    if (!admin.adminExists()) {
        std::string firstName, lastName;
        std::cout << "No admin account found. Create a new admin account.\n";
        std::cout << "Enter first name: ";
        std::cin >> firstName;
        std::cout << "Enter last name: ";
        std::cin >> lastName;
        admin.createAdmin(firstName, lastName);
        std::cout << "Admin account created successfully.\n";
    }

    bool adminLoggedIn = false;
    while (!adminLoggedIn) {
        displayAdminMenu();
        int option;
        std::cin >> option;

        std::string firstName, lastName;
        switch (option) {
            case 1:
                std::cout << "Enter first name: ";
                std::cin >> firstName;
                std::cout << "Enter last name: ";
                std::cin >> lastName;
                if (admin.login(firstName, lastName)) {
                    std::cout << "Login successful!\n";
                    adminLoggedIn = true;
                } else {
                    std::cout << "Invalid credentials. Try again.\n";
                }
                break;
            case 2:
                std::cout << "Enter new first name: ";
                std::cin >> firstName;
                std::cout << "Enter new last name: ";
                std::cin >> lastName;
                admin.createAdmin(firstName, lastName);
                std::cout << "Admin account created successfully.\n";
                break;
            case 3:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    while (true) {
        displayMainMenu();
        int option;
        std::cin >> option;

        std::string name, position, starterName, subName;
        int rating;
        switch (option) {
            case 1:
                std::cout << "Enter player name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter rating: ";
                std::cin >> rating;
                std::cin.ignore();
                std::cout << "Enter position: ";
                std::getline(std::cin, position);
                std::cout << "Is the player a starter (1 for Yes, 0 for No): ";
                bool isStarter;
                std::cin >> isStarter;
                if (admin.addPlayer(name, rating, position, isStarter)) {
                    std::cout << "Player added successfully.\n";
                } else {
                    std::cout << "Failed to add player.\n";
                }
                break;
            case 2:
                std::cout << "Enter player name to release: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                admin.releasePlayer(name);
                std::cout << "Player released successfully.\n";
                break;
            case 3:
                admin.startMatch();
                break;
            case 4:
                admin.startTraining();
                break;
            case 5:
                std::cout << "Enter starter player name: ";
                std::cin.ignore();
                std::getline(std::cin, starterName);
                std::cout << "Enter substitute player name: ";
                std::getline(std::cin, subName);
                if (admin.substitutePlayer(starterName, subName)) {
                    std::cout << "Player substituted successfully.\n";
                } else {
                    std::cout << "Substitution failed.\n";
                }
                break;
            case 6:
                admin.saveAdminData();
                std::cout << "Team data saved successfully.\n";
                break;
            case 7:
                admin.loadAdminData();
                std::cout << "Team data loaded successfully.\n";
                break;
            case 8:
                team.displayTeam();
                break;
            case 9:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
