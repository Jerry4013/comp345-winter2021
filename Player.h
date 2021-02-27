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
    int getNumberOfOwnedTerritories() const;
    void setNumberOfOwnedTerritories(int ownedTerritories);
    int getNumberOfOwnedContinents() const;
    void setNumberOfOwnedContinents(int ownedContinents);
    vector<Territory *> getTerritories() const;
    void setTerritories(vector<Territory*>& territories);
    vector<Card*> getCards() const;
    void setCards(vector<Card*>& cards);

private:
    int id;
    string firstName;
    string lastName;
    string color;
    int biding;                     // 游戏开始时，该玩家愿意出多少钱
    int coins;                      // 手上还有多少钱
    int score;                      // 现在有多少分了
    int remainingCity;              // 一共3个城，还有多少城可以用
    int remainingCubes;             // 一共18个军队，还有多少军队可以用
    int numberOfOwnedTerritories;   // 有多少地区是我占领的，能给我加分
    int numberOfOwnedContinents;    // 有多少大陆是我占领的，能给我加分
    vector<Territory*> territories; // 该玩家有兵或有城堡的区域
    vector<Card*> cards;            // 该玩家手上所有的卡牌
};

