#include "Player.h"
#include "MapLoader.h"
#include <sstream>

Player::Player() {
    id = 0;
    firstName = "Alice";
    lastName = "Lee";
    color = "white";
    bidding = 0;
    coins = 12;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    initializeDefaultValues();
}

Player::Player(int id, const string& firstName, const string& lastName, const string& color, int bidding, int coins,
               vector<Territory *> territories) {
    this->id = id;
    this->firstName = firstName;
    this->lastName = lastName;
    this->color = color;
    this->bidding = bidding;
    this->coins = coins;
    score = 0;
    remainingCity = 3;
    remainingCubes = 18;
    this->territories = territories;
    initializeDefaultValues();
}

Player::Player(const Player& player) {
    id = player.id;
    firstName = player.firstName;
    lastName = player.lastName;
    color = player.color;
    bidding = player.bidding;
    coins = player.coins;
    score = player.score;
    remainingCity = player.remainingCity;
    remainingCubes = player.remainingCubes;
    territories = player.territories;
    cards = player.cards;
    abilities = player.abilities;
    cardTypeVp = player.cardTypeVp;
    cardSetVp = player.cardSetVp;
    oneVpPer3Coins = player.oneVpPer3Coins;
    oneVpPerFlying = player.oneVpPerFlying;
    players = player.players;
    numberOfCardsOfEachType = player.numberOfCardsOfEachType;
    oneVpPer3Coins = player.oneVpPer3Coins;
    oneVpPerFlying = player.oneVpPerFlying;
}

void Player::initializeDefaultValues() {
    abilities[moving] = 0;
    abilities[army] = 0;
    abilities[flying] = 0;
    abilities[elixir] = 0;
    abilities[immuneAttack] = 0;
    numberOfCardsOfEachType[night] = 0;
    numberOfCardsOfEachType[cursed] = 0;
    numberOfCardsOfEachType[arcane] = 0;
    numberOfCardsOfEachType[ancient] = 0;
    numberOfCardsOfEachType[dire] = 0;
    numberOfCardsOfEachType[forest] = 0;
    numberOfCardsOfEachType[noble] = 0;
    numberOfCardsOfEachType[mountain] = 0;
    numberOfCardsOfEachType[emptyKind] = 0;
    oneVpPer3Coins = false;
    oneVpPerFlying = false;
}

Player::~Player() {
    for (auto & territory : territories) {
        territory = nullptr;
    }
    for (auto & player : players) {
        player = nullptr;
    }
    for (auto & card : cards) {
        card = nullptr;
    }
}

void Player::PayCoin(int costOfCard) {
    if (coins < costOfCard) {
        cout << "ERROR! You don't have enough coin to buy this card!" << endl;
        return;
    }
    coins -= costOfCard;
    cout << "Player " << id << " paid " << costOfCard << " coins. Coins left: " << coins << endl;
}

void Player::PlaceNewArmies(int numberOfNewArmies, Territory* territory) {
    territory->placeNewArmiesOfPlayer(id, numberOfNewArmies);
    remainingCubes -= numberOfNewArmies;
    cout << "Player " << id << " place " << numberOfNewArmies << " new armies in territory " << territory->getId()
        << endl;
}

int Player::MoveArmies(int numberOfArmies, Territory *from, Territory *to, int movingPoints) {
    int troopsAtSourceTerritory = from->getArmiesOfPlayer(id);
    if (troopsAtSourceTerritory < numberOfArmies) {
        cout << "There is not enough troop to move!";
        return movingPoints;
    }
    if (numberOfArmies > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Try again.";
        return movingPoints;
    }
    from->removeArmiesOfPlayer(id, numberOfArmies);
    to->placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from->getId() << " to " << to->getId() << endl;
    return movingPoints - numberOfArmies;
}

int Player::MoveOverLand(int numberOfArmies, Territory* from, Territory* to, int movingPoints) {
    int troopsAtSourceTerritory = from->getArmiesOfPlayer(id);
    if (troopsAtSourceTerritory < numberOfArmies) {
        cout << "There is not enough troop to move!";
        return movingPoints;
    }
    int cost = 3;
    if (abilities[flying] == 1) {
        cost = 2;
    } else if (abilities[flying] >= 2) {
        cost = 1;
    }
    if (numberOfArmies * cost > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Try again.";
        return movingPoints;
    }
    from->removeArmiesOfPlayer(id, numberOfArmies);
    to->placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from->getId() << " to " << to->getId() << endl;
    return movingPoints - numberOfArmies * cost;
}

void Player::BuildCity(Territory* territory) {
    if (remainingCity == 0) {
        cout << "You have no city in hand!";
        return;
    }
    remainingCity--;
    territory->buildCity(id);
}

int Player::DestroyArmy(int numberOfArmies, Player* otherPlayer, Territory* territory, int destroyPoints) {
    int currTroops = territory->getArmiesOfPlayer(otherPlayer->getId());
    if (currTroops < numberOfArmies) {
        cout << "There is not enough troop to destroy!";
        return destroyPoints;
    }
    otherPlayer->remainingCubes += numberOfArmies;
    territory->removeArmiesOfPlayer(otherPlayer->getId(), numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " << territory->getId() << endl;
    return destroyPoints - numberOfArmies;
}

bool Player::AndOrAction(Card *card) {
    if (!card->getAnd() && !card->getOr()) {
        cout << "ERROR! This is neither an And card nor an Or card." << endl;
        return false;
    }
    if (card->getAnd() && card->getOr()) {
        cout << "ERROR! A card cannot be both And card and Or card." << endl;
        return false;
    }
    if (card->getAnd()) {
        bool result1 = takeAction(card->getActions()[0]);
        bool result2 = takeAction(card->getActions()[1]);
        return result1 && result2;
    }
    // It must be an "Or card" now.
    int option;
    cout << "You may choose one action below: " << endl;
    cout << "1. " << card->getActions()[0] << endl;
    cout << "2. " << card->getActions()[1] << endl;
    cout << ">>";
    cin >> option;
    return takeAction(card->getActions()[option - 1]);
}

bool Player::takeAction(Action action) {
    if (action.actionType == ActionType::placeArmy && abilities[AbilityType::army] > 0) {
        cout << "Using ability! you can place extra " << abilities[AbilityType::army] << " armies!\n" << endl;
        action.amount += abilities[AbilityType::army];
    }
    if (action.actionType == ActionType::moveArmy && abilities[AbilityType::moving] > 0) {
        cout << "Using ability! you can move extra " << abilities[AbilityType::moving] << " armies!\n" << endl;
        action.amount += abilities[AbilityType::moving];
    }
    while (action.amount > 0) {
        int option;
        cout << "--------------------------------------" << endl;
        cout << "You can " << action << endl;
        cout << "--------------------------------------" << endl;
        cout << "Please choose one option:" << endl;
        cout << "1. Take action." << endl;
        cout << "2. Done." << endl;
        cout << ">>";
        cin >> option;
        if (option == 2) {
            break;
        }
        if (action.actionType == placeArmy) {
            int remainingPoints = placeNewArmiesPrompt(action.amount);
            if (remainingPoints == action.amount) {
                continue;
            }
            action.amount = remainingPoints;
        } else if (action.actionType == moveArmy) {
            int remainingPoints = moveArmiesPrompt(action.amount);
            if (remainingPoints == action.amount) {
                continue;
            }
            action.amount = remainingPoints;
        } else if (action.actionType == buildCity) {
            cout << "Game rule: You may place a city anywhere on the board where you have an army." << endl;
            printMyTerritoriesWithArmies();
            int territoryId;
            cout << "Please choose a territory ID to build a city: " << endl;
            cout << ">>";
            cin >> territoryId;
            Territory* territory = getTerritoryById(territoryId);
            BuildCity(territory);
            action.amount -= 1;
        } else if (action.actionType == destroyArmy) {
            int remainingPoints = destroyArmyPrompt(action.amount);
            if (remainingPoints == action.amount) {
                continue;
            }
            action.amount = remainingPoints;
        }
    }
    return true;
}

int Player::placeNewArmiesPrompt(int movingPoints) {
    cout << "Game rule: You may place new armies only on the starting region or on a region where you have a city."
        << endl;
    printTerritoriesForNewArmies();
    int territoryId, numberOfArmies;
    cout << "Please choose a territory ID to place the new armies: " << endl;
    cout << ">>";
    cin >> territoryId;

    // You may place new armies only on the starting region or on a region where you have a city.
    Territory* territory = getTerritoryById(territoryId);
    if (!territory->getIsStartingRegion() && territory->getCities()[id] == 0) {
        cout << "ERROR! You may place new armies only on the starting region or on a region where"
                " you have a city." << endl;
        return movingPoints;
    }

    cout << "Please enter the number of armies to place: " << endl;
    cout << ">>";
    cin >> numberOfArmies;
    if (numberOfArmies > movingPoints) {
        cout << "ERROR! You can place " << movingPoints << " new armies at most." << endl;
    } else if (numberOfArmies < 1) {
        cout << "ERROR! Please select a valid number." << endl;
    } else if (remainingCubes < numberOfArmies) {
        cout << "ERROR! You don't have enough cubes in hand!" << endl;
    } else {
        PlaceNewArmies(numberOfArmies, territory);
        movingPoints -= numberOfArmies;
    }
    return movingPoints;
}

int Player::moveArmiesPrompt(int movingPoints) {
    printMyTerritoriesWithArmies();
    printNeighborsOfTerritoriesWithArmies();
    int fromTerritoryId, toTerritoryId, numberOfArmies;
    cout << "Please choose a territory ID as starting point: " << endl;
    cout << ">>";
    cin >> fromTerritoryId;
    cout << "Please choose a territory ID as target: " << endl;
    cout << ">>";
    cin >> toTerritoryId;
    cout << "Please choose the number of armies you want to move: " << endl;
    cout << ">>";
    cin >> numberOfArmies;
    Territory* fromTerritory = getTerritoryById(fromTerritoryId);
    Territory* toTerritory = getTerritoryById(toTerritoryId);
    if (fromTerritory->getContinentId() == toTerritory->getContinentId()) {
        int remainingMovingPoints = MoveArmies(numberOfArmies, fromTerritory, toTerritory, movingPoints);
        if (remainingMovingPoints == movingPoints) {
            cout << "ERROR! Please try again." << endl;
        } else {
            movingPoints = remainingMovingPoints;
        }
    } else {
        int remainingMovingPoints = MoveOverLand(numberOfArmies, fromTerritory, toTerritory, movingPoints);
        if (remainingMovingPoints == movingPoints) {
            cout << "ERROR! Please try again." << endl;
        } else {
            movingPoints = remainingMovingPoints;
        }
    }
    return movingPoints;
}

int Player::destroyArmyPrompt(int destroyPoints) {
    int playerId, territoryId;
    cout << "Please choose a player ID to destroy army: " << endl;
    cout << ">>";
    cin >> playerId;
    if (getPlayerById(playerId)->abilities[immuneAttack] > 0) {
        cout << "This player is immune to attack!";
        return destroyPoints;
    }
    cout << "This player has armies in the following regions:" << endl;
    for (auto & territory : territories) {
        int numOfArmies = territory->getArmiesOfPlayer(playerId);
        if (numOfArmies > 0) {
            cout << "TerritoryId " << territory->getId() << ": " << numOfArmies << " armies; ";
        }
    }
    cout << endl;
    cout << "Please choose a territory ID to destroy the army: " << endl;
    cout << ">>";
    cin >> territoryId;
    Player* otherPlayer = getPlayerById(playerId);
    Territory* territory = getTerritoryById(territoryId);
    int remainingMovingPoints = DestroyArmy(1, otherPlayer, territory, destroyPoints);
    return remainingMovingPoints;
}

void Player::exchange(Card *card) {
    cards.emplace_back(card);
    numberOfCardsOfEachType[card->getType()]++;
    for (int i = 0; i < card->getAbilities().size(); ++i) {
        cout << "You gain a new ability: " << card->getAbilities()[i] << "\n\n";
        // Add this ability to the player's abilities attribute
        AbilityType abilityType = card->getAbilities()[i].abilityType;
        if (abilityType == gainCoins) {
            coins += card->getAbilities()[i].amount;
        } else if (abilityType == VP) {
            if (card->getAbilities()[i].vpType == cardType) {
                cardTypeVp.emplace_back(card->getAbilities()[i].cardTypeForVP);
            } else if (card->getAbilities()[i].vpType == cardSet) {
                cardSetVp.emplace_back(card->getAbilities()[i].cardTypeForVP);
            } else if (card->getAbilities()[i].vpType == coinsLeft) {
                oneVpPer3Coins = true;
            } else if (card->getAbilities()[i].vpType == vpPerFlying) {
                oneVpPerFlying = true;
            }
        } else {
            abilities[abilityType] += card->getAbilities()[i].amount;
        }
    }
}

Territory *Player::getTerritoryById(int territoryId) {
    for (auto & territory : territories) {
        if (territory->getId() == territoryId) {
            return territory;
        }
    }
    cout << "ERROR! There is no territory with this ID." << endl;
    return nullptr;
}

Player* Player::getPlayerById(int playerId) {
    for (auto & player : players) {
        if (player->getId() == playerId) {
            return player;
        }
    }
    cout << "ERROR! There is no player with this ID." << endl;
    return nullptr;
}

map<AbilityType, int> Player::getAbilities() const {
    return abilities;
}

void Player::addScore(int newScore) {
    score += newScore;
}

Player &Player::operator=(const Player &player) {
    firstName = player.firstName;
    bidding = player.bidding;
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
    ss << "bidding=" << bidding << "; ";
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
    out << "bidding: " << player.bidding << "; ";
    out << "coins: " << player.coins << "; ";
    out << "score: " << player.score << "; \n";
    out << "remainingCity: " << player.remainingCity << "; ";
    out << "remainingCubes: " << player.remainingCubes << "; \n";
    out << "territories=[";
    vector<int> hasForceInTerritory;
    for (int i = 0; i < player.territories.size(); i++) {
        if (player.territories[i]->getArmies()[player.getId()] > 0 ||
            player.territories[i]->getCities()[player.getId()] > 0) {
            hasForceInTerritory.emplace_back(player.territories[i]->getId());
        }
    }
    for (int i = 0; i < hasForceInTerritory.size(); i++) {
        out << hasForceInTerritory[i];
        if (i < hasForceInTerritory.size() - 1) {
            out << ", ";
        }
    }
    out << "]\ncards=[";
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
    return bidding;
}

void Player::setBidding(int newBiding) {
    bidding = newBiding;
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

void Player::setPlayers(vector<Player*> newPlayers) {
    this->players = newPlayers;
}

void Player::setTerritoryAdjacencyList(map<int, vector<int>> territoryAdjacencyList) {
    this->territoryAdjacencyList = territoryAdjacencyList;
}

void Player::printMyTerritoriesWithArmies() {
    cout << "My Territories With Armies:" << endl;
    for (auto & territory : territories) {
        if (territory->getArmies()[id] > 0) {
            cout << "Territory" << territory->getId() << " (" << territory->getArmies()[id] << " armies), ";
        }
    }
    cout << endl;
}

void Player::printNeighborsOfTerritoriesWithArmies() {
    cout << "Neighbors of these territories: " << endl;
    for (auto & territory : territories) {
        int numOfArmies = territory->getArmies()[id];
        if (numOfArmies > 0) {
            cout << "Territory" << territory->getId() << " (" << numOfArmies << " armies) -> ";
            vector<int> neighbors = territoryAdjacencyList[territory->getId()];
            for (int neighbor : neighbors) {
                int distance = 1;
                if (territory->getContinentId() != getTerritoryById(neighbor)->getContinentId()) {
                    distance = 3;
                }
                cout << "Territory" << neighbor << " (distance " << distance << "), ";
            }
            cout << endl;
        }
    }
}

void Player::printTerritoriesForNewArmies() {
    cout << "You may place new armies in these territories: ";
    for (auto & territory : territories) {
        if (territory->getIsStartingRegion() || territory->getCities()[id] > 0) {
            cout << territory->getId() << ", ";
        }
    }
    cout << endl;
}

vector<CardType> Player::getCardTypeVp() {
    return cardTypeVp;
}

vector<CardType> Player::getCardSetVp() {
    return cardSetVp;
}

unordered_map<CardType, int> Player::getNumberOfCardsOfEachType() {
    return numberOfCardsOfEachType;
}

bool Player::hasOneVpPer3Coins() {
    return oneVpPer3Coins;
}

bool Player::hasOneVpPerFlying() {
    return oneVpPerFlying;
}


