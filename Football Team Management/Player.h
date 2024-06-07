#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name, int rating, const std::string& position);

    void setPosition(const std::string& position);
    void setFitnessLevel(int level);
    void setRating(int rating);

    std::string getName() const;
    int getRating() const;
    std::string getPosition() const;
    int getFitnessLevel() const;

private:
    std::string name;
    int rating;
    std::string position;
    int fitnessLevel;
};

#endif // PLAYER_H
