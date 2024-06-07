#include "Admin.h"
#include <fstream>
#include <iostream>
#include <sstream>

Admin::Admin(Team& team) : team(team) {}

bool Admin::login(const std::string& inputFirstName, const std::string& inputLastName) {
    std::ifstream file("admins.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string storedFirstName, storedLastName;
            iss >> storedFirstName >> storedLastName;
            if (storedFirstName == inputFirstName && storedLastName == inputLastName) {
                firstName = storedFirstName;
                lastName = storedLastName;
                if (fileExists("admin_" + firstName + "_" + lastName + ".txt")) {
                    loadAdminData(); // Load the team data after successful login
                }
                return true;
            }
        }
        file.close();
    }
    return false;
}

void Admin::createAdmin(const std::string& newFirstName, const std::string& newLastName) {
    std::ofstream file("admins.txt", std::ios::app); // Append to the file
    if (file.is_open()) {
        file << newFirstName << " " << newLastName << "\n";
        file.close();
        firstName = newFirstName;
        lastName = newLastName;
        saveAdminData(); // Save the new admin data
    }
}

bool Admin::adminExists() const {
    std::ifstream file("admins.txt");
    return file.good();
}

bool Admin::addPlayer(const std::string& name, int rating, const std::string& position, bool isStarter) {
    Player newPlayer(name, rating, position);
    bool success = team.addPlayer(newPlayer, isStarter);
    if (success) {
        saveAdminData(); // Automatically save data after adding a player
    }
    return success;
}

void Admin::releasePlayer(const std::string& playerName) {
    team.releasePlayer(playerName);
    saveAdminData(); // Automatically save data after releasing a player
}

void Admin::startMatch() {
    team.startMatch();
    saveAdminData(); // Automatically save data after starting a match
}

void Admin::startTraining() {
    team.startTraining();
    saveAdminData(); // Automatically save data after training
}

bool Admin::substitutePlayer(const std::string& starterName, const std::string& subName) {
    bool success = team.substitutePlayer(starterName, subName);
    if (success) {
        saveAdminData(); // Automatically save data after substituting a player
    }
    return success;
}

void Admin::saveAdminData() const {
    std::string filename = "admin_" + firstName + "_" + lastName + ".txt";
    std::ofstream file(filename);
    if (file.is_open()) {
        std::cout << "Saving admin data to " << filename << std::endl;
        // Save admin info
        file << firstName << " " << lastName << "\n";

        // Save team data
        for (const auto& player : team.getAllPlayers()) {
            file << player.getName() << "|" << player.getRating() << "|" << player.getPosition() << "|" << player.getFitnessLevel() << "\n";
        }
        file.close();
        std::cout << "Admin data saved successfully." << std::endl;
    } else {
        std::cerr << "Failed to open file for saving: " << filename << std::endl;
    }
}

void Admin::loadAdminData() {
    std::string filename = "admin_" + firstName + "_" + lastName + ".txt";
    std::ifstream file(filename);
    if (file.is_open()) {
        std::cout << "Loading admin data from " << filename << std::endl;
        std::string line;
        std::getline(file, line); // Ignore the first line since it's the admin info

        team.clear(); // Clear the current team data
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, position;
            int rating, fitnessLevel;

            std::getline(iss, name, '|');
            iss >> rating;
            iss.ignore(1, '|');
            std::getline(iss, position, '|');
            iss >> fitnessLevel;

            Player player(name, rating, position);
            player.setFitnessLevel(fitnessLevel);
            team.addPlayer(player, team.getAllPlayers().size() < 11); // Ensure correct starter and substitute assignment
        }
        file.close();
        std::cout << "Admin data loaded successfully." << std::endl;
    } else {
        std::cerr << "Failed to open file for loading: " << filename << std::endl;
    }
}

bool Admin::fileExists(const std::string& filename) const {
    std::ifstream file(filename);
    return file.good();
}
