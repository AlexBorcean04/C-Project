#ifndef ADMIN_H
#define ADMIN_H

#include "Team.h"
#include <string>

class Admin {
private:
    Team& team;
    std::string firstName;
    std::string lastName;

    bool fileExists(const std::string& filename) const;

public:
    Admin(Team& team);

    bool login(const std::string& inputFirstName, const std::string& inputLastName);
    void createAdmin(const std::string& newFirstName, const std::string& newLastName);
    bool adminExists() const;

    bool addPlayer(const std::string& name, int rating, const std::string& position, bool isStarter);
    void releasePlayer(const std::string& playerName);

    void startMatch();
    void startTraining();
    bool substitutePlayer(const std::string& starterName, const std::string& subName);

    void saveAdminData() const;
    void loadAdminData();
};

#endif // ADMIN_H
