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

Player::Player(const string &name, int biding, int coins, vector<Territory *> &territories) {
    this->name = name;
    this->biding = biding;
    this->coins = coins;
    this->territories = territories;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    numberOfOwnedTerritories = 0;
    numberOfOwnedContinents = 0;
}

Player::~Player() {

}

void Player::PayCoin(int costOfCard) {
    coins -= costOfCard;
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
    return biding;
}

void Player::setBiding(int biding) {
    this->biding = biding;
}

int Player::getCoins() const {
    return coins;
}

void Player::setCoins(int coins) {
    this->coins = coins;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int score) {
    this->score = score;
}

int Player::getRemainingCity() const {
    return remainingCity;
}

void Player::setRemainingCity(int city) {
    this->remainingCity = city;
}

int Player::getRemainingCubes() const {
    return remainingCubes;
}

void Player::setRemainingCubes(int cubes) {
    this->remainingCubes = cubes;
}

int Player::getNumberOfOwnedTerritories() const {
    return numberOfOwnedTerritories;
}

void Player::setNumberOfOwnedTerritories(int ownedTerritories) {
    this->numberOfOwnedTerritories = ownedTerritories;
}

int Player::getNumberOfOwnedContinents() const {
    return numberOfOwnedContinents;
}

void Player::setNumberOfOwnedContinents(int ownedContinents) {
    this->numberOfOwnedContinents = ownedContinents;
}

vector<Territory *> Player::getTerritories() const {
    return territories;
}

void Player::setTerritories(vector<Territory *> &territories) {
    this->territories = territories;
}

vector<Card *> Player::getCards() const {
    return cards;
}

void Player::setCards(vector<Card *> &cards) {
    this->cards = cards;
}


