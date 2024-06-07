#include "Player.h"

Player::Player(const std::string& name, int rating, const std::string& position)
    : name(name), rating(rating), position(position), fitnessLevel(100) {}  // Initialize fitness level to 100

void Player::setPosition(const std::string& position) {
    this->position = position;
}

void Player::setFitnessLevel(int level) {
    this->fitnessLevel = level;
}

void Player::setRating(int rating) {
    this->rating = rating;
}

std::string Player::getName() const {
    return name;
}

int Player::getRating() const {
    return rating;
}

std::string Player::getPosition() const {
    return position;
}

int Player::getFitnessLevel() const {
    return fitnessLevel;
}
