//
// Created by Liu He on 2020-09-30.
// assignment 1

//#include "Player.h"
#ifndef CARDS_H
#define CARDS_H
#include <vector>
class Deck;
class Hand;
//use enum to set card type
enum CardType{
    bomb, blockade, airlift, diplomacy
};

class Card{
public:
    //default constructor
    Card();
    //constructor with parameter
    Card(CardType t);
    //copy constructor
    Card(const Card &c);
    //play function
    void play(Hand& player, Deck& deck);
//    void play(Player& player, Deck& deck);
    //destructor
    ~Card();
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream &output, const Card &c);
    //assignment operator
    Card& operator = (const Card& obj);
    //get method
    CardType* getCardType();

private:
    CardType* t;

};



class Hand {
public:
    //default constructor
    Hand();
    //destructor
    ~Hand();
    //copy constructor
    Hand(const Hand& obj);
    //assignment operator
    Hand& operator= (const Hand& obj);
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream &output, const Hand &H);
    //get method
    std::vector<Card>* getHandVector();


private:
    std::vector<Card>* handVector;

};

class Deck{
public:
    //default constructor
    Deck();
    //parameter constructor
    Deck(int num);
    //destructor
    ~Deck();
    //copy constructor
    Deck(const Deck& obj);
    //assignment operator
    Deck& operator= (const Deck& obj);
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream &output, const Deck &D);
    //get method
    std::vector<Card>* getDeckVector();
    //draw method
    Card draw(Hand& playerHand);
//    Card draw(Player& player);

private:
    std::vector<Card>* deckVector;

};



#endif //CARDS_H
