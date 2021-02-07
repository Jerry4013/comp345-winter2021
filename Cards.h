//
// Created by Bowen Yang on 2021/1/30.
//
#pragma once


//
// Created by Liu He on 2020-11-22.
//


#include <iostream>
#include <vector>
#include <string>

using namespace std;

//use enum to set card type
enum CardType{
    night, cursed, arcane, ancient, dire, forest,noble,mountain,emptyKind
};
class Deck;
class Card{
public:

    Card();
    //constructor with parameter
    Card(CardType t,std::string name,int number_of_army,int number_of_movement,int buildCity,int elixers,int
    kill_army,int fly_ability,int victory_point,int build_ability,int move_ability,int immune_to_attack,bool
    one_vp_for_night,bool one_vp_for_cursed,bool one_vp_for_arcane,bool one_vp_for_ancient,bool one_vp_for_dire,bool
    one_vp_for_forest,bool one_vp_3_coins,bool one_vp_for_fly,bool three_vp_have_two_mountain ,bool three_vp_four_noble ,bool OR_CARD,int money);
    //constructor


    //copy constructor
    Card(const Card &c);
    //stream insertion operator "to string"
    friend ostream& operator<<(ostream& output, const Card& card);
    //assignment operator
    Card& operator = (const Card& card);

    //getters and setters:
    CardType getType() const;

    void setType(CardType type);

    const string &getName() const;

    void setName(const string &name);

    int getNumberOfArmy() const;

    void setNumberOfArmy(int numberOfArmy);

    int getNumberOfMovement() const;

    void setNumberOfMovement(int numberOfMovement);

    int getBuildCity() const;

    void setBuildCity(int buildCity);

    int getKillArmy() const;

    void setKillArmy(int killArmy);

    int getElixers() const;

    void setElixers(int elixers);

    int getFlyAbility() const;

    void setFlyAbility(int flyAbility);

    int getVictoryPoint() const;

    void setVictoryPoint(int victoryPoint);

    int getBuildAbility() const;

    void setBuildAbility(int buildAbility);

    int getMoveAbility() const;

    void setMoveAbility(int moveAbility);

    int getImmuneToAttack() const;

    void setImmuneToAttack(int immuneToAttack);

    bool isOneVpForNight() const;

    void setOneVpForNight(bool oneVpForNight);

    bool isOneVpForCursed() const;

    void setOneVpForCursed(bool oneVpForCursed);

    bool isOneVpForArcane() const;

    void setOneVpForArcane(bool oneVpForArcane);

    bool isOneVpForAncient() const;

    void setOneVpForAncient(bool oneVpForAncient);

    bool isOneVpForDire() const;

    void setOneVpForDire(bool oneVpForDire);

    bool isOneVpForForest() const;

    void setOneVpForForest(bool oneVpForForest);

    bool isOneVp3Coins() const;

    void setOneVp3Coins(bool oneVp3Coins);

    bool isOneVpForFly() const;

    void setOneVpForFly(bool oneVpForFly);

    bool isThreeVpHaveTwoMountain() const;

    void setThreeVpHaveTwoMountain(bool threeVpHaveTwoMountain);

    bool isThreeVpFourNoble() const;

    void setThreeVpFourNoble(bool threeVpFourNoble);

    bool isOrCard() const;

    void setOrCard(bool orCard);

    int getMoney() const;

    void setMoney(int money);

private:
    CardType type;
    std::string name;
    //actions:
    int number_of_army;
    int number_of_movement;
    int buildCity;
    int kill_army;
    //goods:
    //top functions
    int elixers;
    int fly_ability;
    int victory_point;
    int build_ability;
    int move_ability;
    int immune_to_attack;
    //for victory point counting
    bool one_vp_for_night;
    bool one_vp_for_cursed;
    bool one_vp_for_arcane;
    bool one_vp_for_ancient;
    bool one_vp_for_dire;
    bool one_vp_for_forest;
    bool one_vp_3_coins;
    bool one_vp_for_fly;
    bool three_vp_have_two_mountain;
    bool three_vp_four_noble;
    bool OR_CARD;
    int money;
};

class P{
public:
    void Pay(){
        std::cout<<"player.PayCoin() is called"<<endl;
    }
};

class Hand {
public:
    //default constructor
    Hand();
    explicit Hand(Deck* deck);
    //destructor
    ~Hand();
    //copy constructor
    Hand(const Hand& obj);
    //assignment operator
    Hand& operator= (const Hand& obj);
    //stream insertion operator
    friend ostream& operator<<(ostream& output, const Hand& hand);
    //get method
    std::vector<Card>* getHandVector();
    //exchange method
    Card* exchange(int card_number, P p, Deck* deck);


private:
    std::vector<Card>* handVector;
};

class Deck{
public:
    //default constructor
    Deck();
    //parameter constructor
    Deck(int number_of_players);
    //destructor
    ~Deck();
    //copy constructor
    Deck(const Deck& obj);
    //assignment operator
    Deck& operator= (const Deck& obj);
    //stream insertion operator
    friend ostream& operator<<(ostream& output, const Deck& deck);
    //get method
    std::vector<Card>* getDeckVector();
    //draw method
    Card* draw();


private:
    std::vector<Card>* deckVector;
};





