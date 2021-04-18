#include "Player.h"
#include "MapLoader.h"
#include <sstream>
#include <algorithm>

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
               vector<Territory *> territories, PlayerStrategy *initPlayerStrategy) {
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
    playerStrategy = initPlayerStrategy;
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
    playerStrategy = player.playerStrategy;
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
    int remainingPoints;
    if (from->getContinentId() == to->getContinentId()) {
        remainingPoints = MoveOverLand(numberOfArmies, movingPoints);
    } else {
        remainingPoints = MoveOverWater(numberOfArmies, movingPoints);
    }
    if (remainingPoints == movingPoints) {
        return remainingPoints;
    }
    from->removeArmiesOfPlayer(id, numberOfArmies);
    to->placeNewArmiesOfPlayer(id, numberOfArmies);
    cout << numberOfArmies << " armies were moved from " << from->getId() << " to " << to->getId() << endl;
    return remainingPoints;
}

int Player::MoveOverLand(int numberOfArmies, int movingPoints) {
    if (numberOfArmies > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Please try again." << endl;
        return movingPoints;
    }
    return movingPoints - numberOfArmies;
}

int Player::MoveOverWater(int numberOfArmies, int movingPoints) {
    int cost = 3;
    if (abilities[flying] == 1) {
        cout << "\nFlying level 1! The cost to move over water is 2 per army." << endl;
        cost = 2;
    } else if (abilities[flying] >= 2) {
        cout << "\nFlying level 2! The cost to move over water is 1 per army." << endl;
        cost = 1;
    }
    if (numberOfArmies * cost > movingPoints) {
        cout << "ERROR! You don't have enough moving points. Try again." << endl;
        return movingPoints;
    }
    return movingPoints - numberOfArmies * cost;
}

int Player::BuildCity(Territory* territory, int buildPoints) {
    if (remainingCity <= 0) {
        cout << "You have no city in hand!" << endl;
        return buildPoints;
    }
    remainingCity--;
    territory->buildCity(id);
    return buildPoints - 1;
}

int Player::DestroyArmy(int numberOfArmies, Player* otherPlayer, Territory* territory, int destroyPoints) {
    int currTroops = territory->getArmiesOfPlayer(otherPlayer->getId());
    if (currTroops < numberOfArmies) {
        cout << "There is not enough troop to destroy!" << endl;
        return destroyPoints;
    }
    otherPlayer->remainingCubes += numberOfArmies;
    territory->removeArmiesOfPlayer(otherPlayer->getId(), numberOfArmies);
    cout << numberOfArmies << " armies are destroyed on territory " << territory->getId() << endl;
    return destroyPoints - numberOfArmies;
}

void Player::AndOrAction(Card *card) {
    if (!card->getAnd() && !card->getOr()) {
        cout << "ERROR! This is neither an And card nor an Or card." << endl;
        return;
    }
    if (card->getAnd() && card->getOr()) {
        cout << "ERROR! A card cannot be both And card and Or card." << endl;
        return;
    }
    if (card->getAnd()) {
        takeAction(card->getActions()[0]);
        takeAction(card->getActions()[1]);
        return;
    }
    // It must be an "Or card" now.
    int option = playerStrategy->selectOrCard(card);
    takeAction(card->getActions()[option - 1]);
}

void Player::takeAction(Action action) {
    if (action.actionType == ActionType::placeArmy && abilities[AbilityType::army] > 0) {
        cout << "\nUsing ability! you can place extra " << abilities[AbilityType::army] << " armies!\n" << endl;
        action.amount += abilities[AbilityType::army];
    }
    if (action.actionType == ActionType::moveArmy && abilities[AbilityType::moving] > 0) {
        cout << "\nUsing ability! you can move extra " << abilities[AbilityType::moving] << " armies!\n" << endl;
        action.amount += abilities[AbilityType::moving];
    }
    map<int, int*> remainingCubesMap;
    for (auto & player : players) {
        remainingCubesMap[player->id] = &player->remainingCubes;
    }
    map<int, int> immuneAttackMap;
    for (auto & player : players) {
        immuneAttackMap[player->id] = player->abilities[AbilityType::immuneAttack];
    }
    playerStrategy->takeAction(action, id, territories, remainingCubes,territoryAdjacencyList,
                               abilities[AbilityType::flying], remainingCity,
                               remainingCubesMap, immuneAttackMap);
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

Card *Player::selectCard(Hand *hand, Deck* deck) {
    cardIndex = playerStrategy->selectCard(hand, coins);
    PayCoin(Hand::CARD_COSTS[cardIndex]);
    Card* card = hand->getHandCards()[cardIndex];
    exchange(card);
    hand->exchange(cardIndex + 1, deck);
    return card;
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

void Player::printMyAbilities() {
    cout << "\nMy abilities: ";
    for (const auto &[k, v] : abilities) {
        switch (k) {
            case AbilityType::moving:
                cout << v << " moving, ";
                break;
            case AbilityType::army:
                cout << v << " armies, ";
                break;
            case AbilityType::flying:
                cout << v << " flying, ";
                break;
            case AbilityType::elixir:
                cout << v << " elixir, ";
                break;
            case AbilityType::immuneAttack:
                cout << v << " immune attack, ";
                break;
        }
    }
    cout << "\n\n";
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
    out << "Strategy: " << player.playerStrategy->toString() << endl;
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

void Player::setStrategy(PlayerStrategy* newPlayerStrategy) {
    playerStrategy = newPlayerStrategy;
}

string Player::getStrategy() {
    return playerStrategy->toString();
}


