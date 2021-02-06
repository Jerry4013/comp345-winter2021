#ifndef A1_PLAYER_H
#define A1_PLAYER_H
#include <vector>
#include <string>
#include 'Territory.h'
#include 'Biding.h'
#include 'Cards.h'
#include "Hand.h"

class Player
{
public:
    Player();
    Player(const string& name, int biding, int coins,
           vector<Territory> *territories, vector<Card> *cards);
    ~Player();
    void PayCoin(const int costOfCard);
    void PlaceNewArmies(const int numberOfNewArmies, Territory* territory);
    void MoveArmies(const int numberOfArmies, Territory* from, Territory* to);
    void MoveOverLand(const int numberOfArmies, Territory* from, Territory* to);
    void BuildCity(Territory* territory);
    void DestroyArmy(const int numberOfArmies, Player* player, Territory* territory);

    // Getters and Setters
    string getName() const;
    void setName(const string& name);
    int getBiding() const;
    void setBiding(const int biding);
    int getCoins() const;
    void setCoins(const int coins);
    int getScore() const;
    void setScore(const int score);
    int getRemainingCity() const;
    void setRemainingCity(const int city);
    int getRemainingCubes() const;
    void setRemainingCubes(const int cubes);
    int getNumberOfOwnedTerritories() const;
    void setNumberOfOwnedTerritories(const int ownedTerritories);
    int getNumberOfOwnedContinents() const;
    void setNumberOfOwnedContinents(const int ownedContinents);
    vector<Territory>* getTerritories() const;
    void setTerritories(vector<Territory>& territories);
    vector<Card>* getCards() const;
    void setCards(vector<Card>& cards);

private:
    string name;
    int biding;                     // 游戏开始时，该玩家愿意出多少钱
    int coins;                      // 手上还有多少钱
    int score;                      // 现在有多少分了
    int remainingCity;              // 一共3个城，还有多少城可以用
    int remainingCubes;             // 一共18个军队，还有多少军队可以用
    int numberOfOwnedTerritories;   // 有多少地区是我占领的，能给我加分
    int numberOfOwnedContinents;    // 有多少大陆是我占领的，能给我加分
    vector<Territory> *territories; // 该玩家有兵或有城堡的区域
    vector<Card> *cards;            // 该玩家手上所有的卡牌
};

#endif //A1_PLAYER_H
