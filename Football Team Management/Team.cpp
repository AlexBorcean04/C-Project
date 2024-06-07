#include "Team.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Team::Team() {}

bool Team::addPlayer(const Player& player, bool isStarter) {
    if (playerExists(player.getName())) {
        std::cout << "Player with name " << player.getName() << " already exists.\n";
        return false;
    }
    if (starters.size() == 11 && substitutes.size() == 8) {
        std::cout << "The team is full. Please release a player before adding a new one.\n";
        return false;
    }
    if (isStarter && starters.size() >= 11) {
        std::cout << "Cannot add player as starter, the starters are already full.\n";
        return false;
    }
    if (!isStarter && substitutes.size() >= 8) {
        std::cout << "Cannot add player as substitute, the substitutes are already full.\n";
        return false;
    }
    allPlayers.push_back(player);
    if (isStarter) {
        starters.push_back(player);
    } else {
        substitutes.push_back(player);
    }
    return true;
}

void Team::releasePlayer(const std::string& playerName) {
    auto it = std::remove_if(allPlayers.begin(), allPlayers.end(),
                             [&playerName](const Player& player) {
                                 return player.getName() == playerName;
                             });
    if (it != allPlayers.end()) {
        allPlayers.erase(it, allPlayers.end());
    }

    it = std::remove_if(starters.begin(), starters.end(),
                        [&playerName](const Player& player) {
                            return player.getName() == playerName;
                        });
    if (it != starters.end()) {
        starters.erase(it, starters.end());
    }

    it = std::remove_if(substitutes.begin(), substitutes.end(),
                        [&playerName](const Player& player) {
                            return player.getName() == playerName;
                        });
    if (it != substitutes.end()) {
        substitutes.erase(it, substitutes.end());
    }
}

void Team::updateFitnessLevel(const std::string& playerName, int level) {
    for (auto& player : allPlayers) {
        if (player.getName() == playerName) {
            player.setFitnessLevel(level);
            return;
        }
    }
}

void Team::updateRating(const std::string& playerName, int rating) {
    for (auto& player : allPlayers) {
        if (player.getName() == playerName) {
            player.setRating(rating);
            return;
        }
    }
}

void Team::startMatch() {
    if (starters.size() < 11) {
        std::cout << "Cannot start the match. The team does not have 11 starters.\n";
        return;
    }
    std::cout << "Match started with the following starters:\n";
    for (const auto& player : starters) {
        std::cout << player.getName() << " - " << player.getPosition() << "\n";
    }
    updateFitnessAfterMatch(); // Update fitness levels after the match
}

void Team::startTraining() {
    for (auto& player : allPlayers) {
        player.setRating(player.getRating() + 1); // Increment each player's rating by 1
    }
    std::cout << "Training completed. Players' ratings have been updated.\n";
}

bool Team::substitutePlayer(const std::string& starterName, const std::string& subName) {
    for (size_t i = 0; i < starters.size(); ++i) {
        if (starters[i].getName() == starterName) {
            for (size_t j = 0; j < substitutes.size(); ++j) {
                if (substitutes[j].getName() == subName) {
                    std::swap(starters[i], substitutes[j]);
                    return true;
                }
            }
        }
    }
    return false;
}

void Team::saveData(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& player : allPlayers) {
            file << player.getName() << " " << player.getRating() << " " << player.getPosition() << " " << player.getFitnessLevel() << "\n";
        }
        file.close();
    }
}

void Team::loadData(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string name, position;
        int rating, fitnessLevel;
        allPlayers.clear();
        starters.clear();
        substitutes.clear();
        while (file >> name >> rating >> position >> fitnessLevel) {
            Player player(name, rating, position);
            player.setFitnessLevel(fitnessLevel);
            allPlayers.push_back(player);
            if (starters.size() < 11) { // Load first 11 as starters
                starters.push_back(player);
            } else {
                substitutes.push_back(player);
            }
        }
        file.close();
    }
}

void Team::displayTeam() const {
    std::cout << "Team Roster:\n";
    for (const auto& player : allPlayers) {
        std::cout << "Name: " << player.getName()
                  << ", Rating: " << player.getRating()
                  << ", Position: " << player.getPosition()
                  << ", Fitness Level: " << player.getFitnessLevel() << "\n";
    }
}

void Team::clear() {
    allPlayers.clear();
    starters.clear();
    substitutes.clear();
}

std::vector<Player> Team::getAllPlayers() const {
    return allPlayers;
}

bool Team::playerExists(const std::string& playerName) const {
    for (const auto& player : allPlayers) {
        if (player.getName() == playerName) {
            return true;
        }
    }
    return false;
}

void Team::updateFitnessAfterMatch() {
    for (auto& starter : starters) {
        std::string position = starter.getPosition();
        if (position == "Goalkeeper") {
            starter.setFitnessLevel(starter.getFitnessLevel() - 3);
        } else if (position == "Defender") {
            starter.setFitnessLevel(starter.getFitnessLevel() - 5);
        } else if (position == "Midfielder") {
            starter.setFitnessLevel(starter.getFitnessLevel() - 8);
        } else if (position == "Forward") {
            starter.setFitnessLevel(starter.getFitnessLevel() - 6);
        }
        for (auto& player : allPlayers) {
            if (player.getName() == starter.getName()) {
                player.setFitnessLevel(starter.getFitnessLevel());
            }
        }
    }

    // Set fitness level of substitutes to 100
    for (auto& substitute : substitutes) {
        substitute.setFitnessLevel(100);
        // Synchronize the fitness level with allPlayers
        for (auto& player : allPlayers) {
            if (player.getName() == substitute.getName()) {
                player.setFitnessLevel(100);
            }
        }
    }
}
