#include "Player.h"
#include <sstream>

Player::Player() {
    firstName = "Alice";
    biding = 1;
    coins = 12;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    numberOfOwnedTerritories = 0;
    numberOfOwnedContinents = 0;
}

Player::Player(const string &name, int biding, int coins, vector<Territory *> &territories) {
    this->firstName = name;
    this->biding = biding;
    this->coins = coins;
    this->territories = territories;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    numberOfOwnedTerritories = 0;
    numberOfOwnedContinents = 0;
}

Player::Player(const Player& player) {
    firstName = player.firstName;
    biding = player.biding;
    coins = player.coins;
    score = player.score;
    remainingCity = player.remainingCity;
    remainingCubes = player.remainingCubes;
    numberOfOwnedTerritories = player.numberOfOwnedTerritories;
    numberOfOwnedContinents = player.numberOfOwnedContinents;
    territories = player.territories;
    cards = player.cards;
}

Player::~Player() {
    for (int i = 0; i < territories.size(); ++i) {
        territories[i] = nullptr;
    }
    for (int i = 0; i < cards.size(); ++i) {
        cards[i] = nullptr;
    }
}

void Player::PayCoin(int costOfCard) {
    coins -= costOfCard;
    cout << "Player " + this->firstName + " paid " << costOfCard << endl;
}

void Player::PlaceNewArmies(int numberOfNewArmies, Territory &territory) {
    int currTroops = territory.getArmiesOfPlayer(this->firstName);
    territory.SetNumTroops(this->firstName, currTroops + numberOfNewArmies);
    cout << numberOfNewArmies << " new armies are placed on territory " + territory.getName() << endl;
}

void Player::MoveOverLand(int numberOfArmies, Territory &from, Territory &to) {
    int troopsAtSourceTerritory = from.getArmiesOfPlayer(this->firstName);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return;
    }
    from.SetNumTroops(this->firstName, troopsAtSourceTerritory - numberOfArmies);
    int troopsAtTargetTerritory = to.getArmiesOfPlayer(this->firstName);
    to.SetNumTroops(this->firstName, troopsAtTargetTerritory + numberOfArmies);
    cout << numberOfArmies << " armies were moved from " + from.getName() + " to " + to.getName()
        << endl;
}

void Player::MoveArmies(int numberOfArmies, Territory &from, Territory &to) {
    int troopsAtSourceTerritory = from.getArmiesOfPlayer(this->firstName);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return;
    }
    from.SetNumTroops(this->firstName, troopsAtSourceTerritory - numberOfArmies);
    int troopsAtTargetTerritory = to.getArmiesOfPlayer(this->firstName);
    to.SetNumTroops(this->firstName, troopsAtTargetTerritory + numberOfArmies);
    cout << numberOfArmies << " armies were moved from " + from.getName() + " to " + to.getName()
         << endl;
}

void Player::BuildCity(Territory &territory) {
    int currCity = territory.getCities(this->firstName);
    territory.setCities(this->firstName, currCity + 1);
}

void Player::DestroyArmy(int numberOfArmies, Player &player, Territory &territory) {
    int currTroops = territory.getArmiesOfPlayer(player.firstName);
    if (currTroops < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to destroy!";
        return;
    }
    territory.SetNumTroops(player.firstName, currTroops - numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " + territory.getName() << endl;
}


Player &Player::operator=(const Player &player) {
    firstName = player.firstName;
    biding = player.biding;
    coins = player.coins;
    score = player.score;
    remainingCity = player.remainingCity;
    remainingCubes = player.remainingCubes;
    numberOfOwnedTerritories = player.numberOfOwnedTerritories;
    numberOfOwnedContinents = player.numberOfOwnedContinents;
    territories = player.territories;
    cards = player.cards;
    return *this;
}

string Player::toString() const {
    stringstream ss;
    ss << "Player{ firstName=" << firstName << "; ";
    ss << "biding=" << biding << "; ";
    ss << "coins=" << coins << "; ";
    ss << "score=" << score << "; ";
    ss << "remainingCity=" << remainingCity << "; ";
    ss << "remainingCubes=" << remainingCubes << "; ";
    ss << "numberOfOwnedTerritories=" << numberOfOwnedTerritories << "; ";
    ss << "numberOfOwnedContinents=" << numberOfOwnedContinents << "; ";
    ss << "territories=[";
    for (int i = 0; i < territories.size(); i++) {
        ss << *territories[i];
        if (i < territories.size() - 1) {
            ss << ", ";
        }
    }
    ss << "]; cards=[";
    for (int i = 0; i < cards.size(); i++) {
        ss << *cards[i];
        if (i < cards.size() - 1) {
            ss << ", ";
        }
    }
    ss << "]}";
    return ss.str();
}

ostream &operator<<(ostream &out, const Player &player) {
    out << "Player{ firstName=" << player.firstName << "; ";
    out << "biding=" << player.biding << "; ";
    out << "coins=" << player.coins << "; ";
    out << "score=" << player.score << "; ";
    out << "remainingCity=" << player.remainingCity << "; ";
    out << "remainingCubes=" << player.remainingCubes << "; ";
    out << "numberOfOwnedTerritories=" << player.numberOfOwnedTerritories << "; ";
    out << "numberOfOwnedContinents=" << player.numberOfOwnedContinents << "; ";
    out << "territories=[";
    for (int i = 0; i < player.territories.size(); i++) {
        out << *player.territories[i];
        if (i < player.territories.size() - 1) {
            out << ", ";
        }
    }
    out << "]; cards=[";
    for (int i = 0; i < player.cards.size(); i++) {
        out << *player.cards[i];
        if (i < player.cards.size() - 1) {
            out << ", ";
        }
    }
    out << "]}";
    return out;
}


string Player::getName() const {
    return firstName;
}

void Player::setName(const string &newName) {
    firstName = newName;
}

int Player::getBiding() const {
    return biding;
}

void Player::setBidding(int biding) {
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




