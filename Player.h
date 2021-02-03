#ifndef A1_PLAYER_H
#define A1_PLAYER_H
#include <vector>
#include <string>
#include 'Region.h'
#include 'Biding.h'
#include 'Cards.h'

class Player
{
public:
    Player();
    Player(const string& name, int coins, int cubes, vector<Region> *regions, vector<Card> *cards, int biding);
    ~Player();
    void PayCoin();
    void PlaceNewArmies();
    void MoveArmies();
    void MoveOverLand();
    void BuildCity();
    void DestroyArmy();

    string getName() const;
    void setName(const string& name);
    int getCoins() const;
    void setCoins(const int coins);
    int getCubes() const;
    void setCubes(const int cubes);
    vector<Region>* getRegions() const;
    void setRegions(vector<Region>& regions);
    vector<Card>* getCards() const;
    void setCards(vector<Card>& cards);
    int getBiding() const;
    void setBiding(const int biding);

private:
    string name;
    int coins;
    int cubes;
    vector<Region> *regions;
    vector<Card> *cards;
    int biding;
};

#endif //A1_PLAYER_H
