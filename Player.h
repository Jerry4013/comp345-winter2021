#pragma once
#include <vector>
#include <string>
#include "Map.h"
#include "Cards.h"

class Player {
public:
    Player();
    Player(const string& name, int biding, int coins, vector<Territory*>& territories);
    Player(const Player&);
    Player& operator=(const Player& secondPlayer);
    friend ostream& operator<<(ostream& out, const Player& player);
    string toString() const;
    ~Player();

    void PayCoin(int costOfCard);
    void PlaceNewArmies(int numberOfNewArmies, Territory& territory);
    void MoveArmies(int numberOfArmies, Territory& from, Territory& to);
    void MoveOverLand(int numberOfArmies, Territory& from, Territory& to);
    void BuildCity(Territory& territory);
    void DestroyArmy(int numberOfArmies, Player& player, Territory& territory);

    // Getters and Setters
    int getId() const;
    string getFirstName() const;
    string getLastName() const;
    string getColor() const;
    void setName(const string& newName);
    int getBiding() const;
    void setBidding(int biding);
    int getCoins() const;
    void setCoins(int coins);
    int getScore() const;
    void setScore(int score);
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
};

