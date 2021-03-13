#include "Player.h"
#include <sstream>
#include <iomanip>

Player::Player() {
    firstName = "Alice";
    biding = 1;
    coins = 12;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
}

Player::Player(int id, const string& firstName, const string& lastName, const string& color, int bidding, int coins) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->color = color;
    this->biding = bidding;
    this->coins = coins;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
}

Player::Player(const Player& player) {
    id = player.id;
    firstName = player.firstName;
    lastName = player.lastName;
    color = player.color;
    biding = player.biding;
    coins = player.coins;
    score = player.score;
    remainingCity = player.remainingCity;
    remainingCubes = player.remainingCubes;
    territories = player.territories;
    cards = player.cards;
    abilities = player.abilities;
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
    // TODO: 更新自己的territory
    territory.placeNewArmiesOfPlayer(id, numberOfNewArmies);
    cout << numberOfNewArmies << " new armies are placed on territory " + territory.getName() << endl;
}

int Player::MoveOverLand(int numberOfArmies, Territory &from, Territory &to, int movingPoints) {
    int troopsAtSourceTerritory = from.getArmiesOfPlayer(id);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return movingPoints;
    }
    int cost = 3;
    // TODO 各种abilities要初始化为0
    if (abilities["flying"] == 1) {
        cost = 2;
    } else if (abilities["flying"] >= 2) {
        cost = 1;
    }
    from.removeArmiesOfPlayer(id, numberOfArmies);
    to.placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from.getId() << " to " << to.getId() << endl;
    return movingPoints - numberOfArmies * cost;
}

int Player::MoveArmies(int numberOfArmies, Territory &from, Territory &to, int movingPoints) {
    int troopsAtSourceTerritory = from.getArmiesOfPlayer(id);
    if (troopsAtSourceTerritory < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to move!";
        return movingPoints;
    }
    from.removeArmiesOfPlayer(id, numberOfArmies);
    to.placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from.getId() << " to " << to.getId() << endl;
    return movingPoints - numberOfArmies;
}

void Player::BuildCity(Territory &territory) {
    if (remainingCity == 0) {
        cout << "You have no city in hand!";
        return;
    }
    remainingCity--;
    territory.buildCity(id);
}

int Player::DestroyArmy(int numberOfArmies, int playerId, Territory &territory, int destroyPoints) {
    int currTroops = territory.getArmiesOfPlayer(playerId);
    if (currTroops < numberOfArmies) {
        // throw an exception
        cout << "There is not enough troop to destroy!";
        return destroyPoints;
    }
    territory.removeArmiesOfPlayer(playerId, numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " << territory.getId() << endl;
    return destroyPoints - numberOfArmies;
}


Player &Player::operator=(const Player &player) {
    firstName = player.firstName;
    biding = player.biding;
    coins = player.coins;
    score = player.score;
    remainingCity = player.remainingCity;
    remainingCubes = player.remainingCubes;
    territories = player.territories;
    cards = player.cards;
    return *this;
}

string Player::toString() const {
    stringstream ss;
    ss << "Player{ firstName=" << firstName << "; ";
    ss << "biding=" << biding << "; ";
    ss << "coinSupply=" << coins << "; ";
    ss << "score=" << score << "; ";
    ss << "remainingCity=" << remainingCity << "; ";
    ss << "remainingCubes=" << remainingCubes << "; ";
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
    out << "Player " << player.id << ": " << player.firstName << " " << player.lastName
        << " (" << player.color << ")" << endl;
    out << "------------------------------------------" << endl;
    out << "biding: " << player.biding << "; ";
    out << "coins: " << player.coins << "; ";
    out << "score: " << player.score << "; \n";
    out << "remainingCity: " << player.remainingCity << "; ";
    out << "remainingCubes: " << player.remainingCubes << "; \n";
    out << "territories=[";
    for (int i = 0; i < player.territories.size(); i++) {
        out << player.territories[i]->getId();
        if (i < player.territories.size() - 1) {
            out << ", ";
        }
    }
    out << "]\n; cards=[";
    for (int i = 0; i < player.cards.size(); i++) {
        out << player.cards[i]->getName();
        if (i < player.cards.size() - 1) {
            out << ", ";
        }
    }
    out << "]\n\n";
    return out;
}

int Player::getId() const {
    return id;
}

void Player::setId(int newId) {
    id = newId;
}

string Player::getFirstName() const {
    return firstName;
}

void Player::setFirstName(string &newFirstName) {
    firstName = newFirstName;
}

string Player::getLastName() const {
    return lastName;
}

void Player::setLastName(string &newLastName) {
    lastName = newLastName;
}

string Player::getColor() const {
    return color;
}

void Player::setColor(string &newColor) {
    color = newColor;
}

int Player::getBiding() const {
    return biding;
}

void Player::setBidding(int newBiding) {
    biding = newBiding;
}

int Player::getCoins() const {
    return coins;
}

void Player::setCoins(int newCoins) {
    coins = newCoins;
}

int Player::getScore() const {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
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




