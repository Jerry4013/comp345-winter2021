//
// Created by Bowen Yang on 2021/1/30.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// TODO: 写toString，否则没办法显示。
enum CardType{
    night, cursed, arcane, ancient, dire, forest, noble, mountain, emptyKind
};

enum AbilityType {
    moving, army, flying, elixir, gainCoins, VP, immuneAttack
};

enum ActionType {
    placeArmy, moveArmy, buildCity, destroyArmy
};

enum VPType {
    nullVpType, cardType, cardSet, coinsLeft, vpPerFlying
};

struct Ability {
    AbilityType abilityType;
    int amount;
    VPType vpType;          // if abilityType == VP, then there is a vpType
    CardType cardTypeForVP; // If the VP type is cardType or cardSet, cardTypeForVP is used to specify the type.
    friend ostream& operator<<(ostream& output, const Ability& action);
};

struct Action {
    ActionType actionType;
    int amount;
    friend ostream& operator<<(ostream& output, const Action& action);
};

class Card{
public:
    Card();
    Card(CardType cardType, string name, vector<Ability> abilities, vector<Action> actions, bool isAndCard,
         bool isOrCard);
    Card(const Card&);
    ~Card();
    friend ostream& operator<<(ostream& output, const Card& card);
    Card& operator=(const Card& card);

    //getters and setters:
    CardType getType() const;
    void setType(CardType newCardType);
    string getName() const;
    void setName(string& newName);
    vector<Ability> getAbilities();
    vector<Action> getActions();
    bool getAnd() const;
    bool getOr() const;
    static string cardTypeToString(CardType cardTypeToString);

private:
    CardType cardType;
    string name;
    vector<Ability> abilities;
    vector<Action> actions;
    bool isAndCard;
    bool isOrCard;
};

class Deck{
public:
    //default constructor
    Deck();
    //parameter constructor
    Deck(int numberOfPlayers);
    //destructor
    ~Deck();
    //copy constructor
    Deck(const Deck&);
    //assignment operator
    Deck& operator=(const Deck& obj);
    //stream insertion operator
    friend ostream& operator<<(ostream& output, const Deck& deck);
    //get method
    vector<Card*> getCards();
    //draw method
    Card* draw();
    void shuffleDeck();

private:
    vector<Card*> cards;
    void initializeDeckOfTwoPlayers();
};

class Hand {
public:
    Hand();
    Hand(Deck *deck);
    ~Hand();
    Hand(const Hand& obj);
    Hand& operator= (const Hand& obj);
    friend ostream& operator<<(ostream& output, const Hand& hand);
    vector<Card*> getHandCards();
    Card* exchange(int cardNumber, Deck* deck);
private:
    vector<Card*> handCards;
    static const vector<int> CARD_COSTS;
};



