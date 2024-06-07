#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <string>

class Team {
public:
    Team();
    bool addPlayer(const Player& player, bool isStarter);
    void releasePlayer(const std::string& playerName);
    void updateFitnessLevel(const std::string& playerName, int level);
    void updateRating(const std::string& playerName, int rating);
    void startMatch();
    void startTraining();
    bool substitutePlayer(const std::string& starterName, const std::string& subName);
    void saveData(const std::string& filename) const;
    void loadData(const std::string& filename);
    void displayTeam() const;
    void clear();

    std::vector<Player> getAllPlayers() const;

private:
    std::vector<Player> starters;
    std::vector<Player> substitutes;
    std::vector<Player> allPlayers;

    bool playerExists(const std::string& playerName) const;
    void updateFitnessAfterMatch();
};

#endif // TEAM_H
