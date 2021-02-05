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
    night, cursed, arcane, ancient, dire, forest,noble,emptyKind
};
class Deck;
class Card{
public:
    //constructor with parameter
    Card(CardType t,std::string name,int number_of_army,int number_of_movement,int buildCity,int elixers,int
    kill_army,int fly_ability,int victory_point,int build_ability,int move_ability,int immune_to_attack,bool
    one_vp_for_night,bool one_vp_for_cursed,bool one_vp_for_arcane,bool one_vp_for_ancient,bool one_vp_for_dire,bool
    one_vp_for_forest,bool one_vp_3_coins,bool one_vp_for_fly,bool OR_CARD);
    //copy constructor
    Card(const Card &c);
    //stream insertion operator "to string"
    friend ostream& operator<<(ostream& output, const Card& card);
    //assignment operator
    Card& operator = (const Card& card);


private:
    CardType type;
    std::string name;
    int number_of_army;
    int number_of_movement;
    int buildCity;
    int elixers;
    int kill_army;
    //top functions
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
    bool OR_CARD;

};

class P{
public:
    void Pay(){

    }
};

class Hand {
public:
    //default constructor
    Hand(Deck* deck);
    //destructor
    ~Hand();
    //copy constructor
    Hand(const Hand& obj);
    //assignment operator
    Hand& operator= (const Hand& obj);
    //stream insertion operator
    friend ostream& operator<<(ostream& output, const Hand& hand);
    //get method
    std::vector<Card*>* getHandVector();
    //exchange method
    // exchange(int card_number, P p, Deck* deck);
    Card * exchange(int card_number, P p, Deck* deck);

private:
    std::vector<Card*>* handVector;
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
    //Card draw();
    Card * draw();


private:
    std::vector<Card>* deckVector;
};





