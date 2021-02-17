#include "Player.h"
#include <sstream>

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

Player::Player(const Player& player) {
    name = player.name;
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
    // do nothing
}

void Player::PayCoin(int costOfCard) {
    coins -= costOfCard;
    cout << "Player " + this->name + " paid " << costOfCard << endl;
}

void Player::PlaceNewArmies(int numberOfNewArmies, Territory &territory) {
    int currTroops = territory.GetNumTroops(this->name);
    territory.SetNumTroops(this->name, currTroops + numberOfNewArmies);
    cout << numberOfNewArmies << " new armies are placed on territory " + territory.GetTerritoryName() << endl;
}

void Player::MoveOverLand(int numberOfArmies, Territory &from, Territory &to) {
    int troopsAtSourceTerritory = from.GetNumTroops(this->name);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return;
    }
    from.SetNumTroops(this->name, troopsAtSourceTerritory - numberOfArmies);
    int troopsAtTargetTerritory = to.GetNumTroops(this->name);
    to.SetNumTroops(this->name, troopsAtTargetTerritory + numberOfArmies);
    cout << numberOfArmies << " armies were moved from " + from.GetTerritoryName() + " to " + to.GetTerritoryName()
        << endl;
}

void Player::MoveArmies(int numberOfArmies, Territory &from, Territory &to) {
    int troopsAtSourceTerritory = from.GetNumTroops(this->name);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return;
    }
    from.SetNumTroops(this->name, troopsAtSourceTerritory - numberOfArmies);
    int troopsAtTargetTerritory = to.GetNumTroops(this->name);
    to.SetNumTroops(this->name, troopsAtTargetTerritory + numberOfArmies);
    cout << numberOfArmies << " armies were moved from " + from.GetTerritoryName() + " to " + to.GetTerritoryName()
         << endl;
}

void Player::BuildCity(Territory &territory) {
    int currCity = territory.getCities(this->name);
    territory.setCities(this->name, currCity + 1);
}

void Player::DestroyArmy(int numberOfArmies, Player &player, Territory &territory) {
    int currTroops = territory.GetNumTroops(player.name);
    if (currTroops < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to destroy!";
        return;
    }
    territory.SetNumTroops(player.name, currTroops - numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " + territory.GetTerritoryName() << endl;
}


Player &Player::operator=(const Player &player) {
    name = player.name;
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
    ss << "Player{ name=" << name << "; ";
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
    out << "Player{ name=" << player.name << "; ";
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




