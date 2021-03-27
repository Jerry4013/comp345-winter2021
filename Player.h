#pragma once
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"

class Player {
public:
    Player();
    Player(int id, const string& firstName, const string& lastName, const string& color, int bidding, int coins,
           vector<Territory *> territories);
    Player(const Player&);
    Player& operator=(const Player& secondPlayer);
    friend ostream& operator<<(ostream& out, const Player& player);
    string toString() const;
    ~Player();

    void exchange(Card* card);
    void PayCoin(int costOfCard);
    void PlaceNewArmies(int numberOfNewArmies, Territory* territory);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    int MoveArmies(int numberOfArmies, Territory* from, Territory* to, int movingPoints);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    int MoveOverLand(int numberOfArmies, int movingPoints);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    int MoveOverWater(int numberOfArmies, int movingPoints);
    int BuildCity(Territory* territory, int buildPoints);
    // return remaining movingPoints. If the return value equals the parameter movingPoints, then this move failed.
    int DestroyArmy(int numberOfArmies, Player* otherPlayer, Territory* territory, int destroyPoints);
    bool AndOrAction(Card* card);
    bool takeAction(Action action);
    void addScore(int newScore);
    void printMyAbilities();

    // Getters and Setters
    int getId() const;
    void setId(int newId);
    string getFirstName() const;
    void setFirstName(string& newFirstName);
    string getLastName() const;
    void setLastName(string& newLastName);
    string getColor() const;
    void setColor(string& newColor);
    int getBiding() const;
    void setBidding(int newBiding);
    int getCoins() const;
    void setCoins(int newCoins);
    int getScore() const;
    void setScore(int newScore);
    int getRemainingCity() const;
    void setRemainingCity(int city);
    int getRemainingCubes() const;
    void setRemainingCubes(int cubes);
    vector<Territory *> getTerritories() const;
    void setTerritories(vector<Territory*>& territories);
    vector<Card*> getCards() const;
    void setCards(vector<Card*>& cards);
    map<AbilityType, int> getAbilities() const;
    void setPlayers(vector<Player*> players);
    void setTerritoryAdjacencyList(map<int, vector<int>> territoryAdjacencyList);
    vector<CardType> getCardTypeVp();
    vector<CardType> getCardSetVp();
    unordered_map<CardType, int> getNumberOfCardsOfEachType();
    bool hasOneVpPer3Coins();
    bool hasOneVpPerFlying();

private:
    int id;
    string firstName;
    string lastName;
    string color;
    int bidding;
    int coins;
    int score;
    int remainingCity;
    int remainingCubes;
    vector<Territory*> territories; // all the territories in the game.
    vector<Player*> players; // All the players in the game. Used when destroying other player's army.
    vector<Card*> cards;
    map<AbilityType, int> abilities; // only handle non-VP abilities: moving, army, flying, elixir, immuneAttack
    vector<CardType> cardTypeVp;
    vector<CardType> cardSetVp;
    bool oneVpPer3Coins;
    bool oneVpPerFlying;
    map<int, vector<int>> territoryAdjacencyList;
    unordered_map<CardType, int> numberOfCardsOfEachType;

    Territory* getTerritoryById(int territoryId);
    void initializeDefaultValues();
    Player* getPlayerById(int playerId);
    int placeNewArmiesPrompt(int movingPoints);
    int moveArmiesPrompt(int movingPoints);
    int destroyArmyPrompt(int destroyPoints);
    int buildCityPrompt(int buildPoints);
    void printMyTerritoriesWithArmies();
    void printNeighborsOfTerritoriesWithArmies();
    void printTerritoriesForNewArmies();
};
