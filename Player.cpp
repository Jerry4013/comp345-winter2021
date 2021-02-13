#include "Player.h"

Player::Player() {
    name = "Alice Lin";
    biding = 1;
    coins = 12;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    numberOfOwnedTerritories = 0;
    numberOfOwnedContinents = 0;
}

Player::Player(const string &name, int biding, int coins, vector<Territory *> &territories, vector<Card *> &cards) {

}

Player::~Player() {

}

void Player::PayCoin(int costOfCard) {

}

void Player::PlaceNewArmies(int numberOfNewArmies, Territory &territory) {

}

void Player::MoveOverLand(int numberOfArmies, Territory &from, Territory &to) {

}

void Player::MoveArmies(int numberOfArmies, Territory &from, Territory &to) {

}

void Player::BuildCity(Territory &territory) {

}

void Player::DestroyArmy(int numberOfArmies, Player &player, Territory &territory) {

}

string Player::getName() const {
    return name;
}

void Player::setName(const string &newName) {
    name = newName;
}

int Player::getBiding() const {
    return 0;
}

void Player::setBiding(int biding) {

}

int Player::getCoins() const {
    return 0;
}

void Player::setCoins(int coins) {

}

int Player::getScore() const {
    return 0;
}

void Player::setScore(int score) {

}

int Player::getRemainingCity() const {
    return 0;
}

void Player::setRemainingCity(int city) {

}

int Player::getRemainingCubes() const {
    return 0;
}

void Player::setRemainingCubes(int cubes) {

}

int Player::getNumberOfOwnedTerritories() const {
    return 0;
}

void Player::setNumberOfOwnedTerritories(int ownedTerritories) {

}

int Player::getNumberOfOwnedContinents() const {
    return 0;
}

void Player::setNumberOfOwnedContinents(int ownedContinents) {

}

vector<Territory *> Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(vector<Territory *> &territories) {

}

vector<Card *> *Player::getCards() const {
    return nullptr;
}

void Player::setCards(vector<Card *> &cards) {

}


