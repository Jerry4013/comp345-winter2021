//
// Created by jerry on 4/3/2021.
//

#ifndef COMP345_WINTER2021_PLAYERSTRATEGIES_H
#define COMP345_WINTER2021_PLAYERSTRATEGIES_H
#include "Cards.h"

class PlayerStrategy {
public:
    virtual int selectCard(Hand *hand, int coins) = 0;
    virtual string toString() = 0;
};

class HumanStrategy : public PlayerStrategy {
public:
    int selectCard(Hand *hand, int coins) override; // return a card index 0-5
    string toString() override;
};

class GreedyComputerStrategy : public PlayerStrategy {
public:
    // return a card index 0-5. This method will choose the first card that building a city or destroying opponents.
    // If no card meets this requirement, it will select the first card, index 0.
    int selectCard(Hand *hand, int coins) override;
    string toString() override;
};

class ModerateComputerStrategy : public PlayerStrategy {
public:
    int selectCard(Hand *hand, int coins) override; // return a card index 0-5
    string toString() override;
};

#endif //COMP345_WINTER2021_PLAYERSTRATEGIES_H
