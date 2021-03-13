#pragma once
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"

class Player {
public:
    Player();
    Player(int id, const string& firstName, const string& lastName, const string& color, int bidding, int coins);
    Player(const Player&);
    Player& operator=(const Player& secondPlayer);
    friend ostream& operator<<(ostream& out, const Player& player);
    string toString() const;
    ~Player();

    void PayCoin(int costOfCard);
    void PlaceNewArmies(int numberOfNewArmies, Territory& territory);
    int MoveArmies(int numberOfArmies, Territory& from, Territory& to, int movingPoints);
    int MoveOverLand(int numberOfArmies, Territory& from, Territory& to, int movingPoints);
    void BuildCity(Territory& territory);
    int DestroyArmy(int numberOfArmies, int playerId, Territory& territory, int destroyPoints);

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

private:
    int id;
    string firstName;
    string lastName;
    string color;
    int biding;
    int coins;
    int score;
    int remainingCity;
    int remainingCubes;
    vector<Territory*> territories;
    vector<Card*> cards;
    map<string, int> abilities;
};
