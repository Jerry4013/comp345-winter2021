#pragma once

#include<iostream>
#include<string>
#include<vector>

#include "Player.h"
#include "Map.h"

class Player;
class Order {
public:
    Order();
    Order(Player* player);
    Order(const Order& toCopy);
    virtual ~Order();
    Order& operator=(const Order& rightSide);

    virtual bool validate() = 0;
    virtual void execute() = 0;
    virtual std::string getType() = 0;

    friend std::ostream& operator<<(std::ostream& out, const Order& toOutput);

protected:
    Player* player;
    bool wasExecuted{ false };

private:
    virtual std::ostream& doPrint(std::ostream& out) const = 0;
};


//deploy: place some armies on one of the current player’s territories.
class Deploy : public Order {
public:
    Deploy();
    Deploy(Player* player, Territory* target ,int numOfArmies);
    Deploy(const Deploy& toCopy);
    ~Deploy();
    Deploy& operator=(const Deploy& rightSide);

    virtual bool validate();
    virtual void execute();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& out, const Deploy& toOutput);

private:
    Territory* territoryToDeploy;
    int numOfArmies;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


//advance: move some armies from one of the current player’s territories (source) to an adjacent territory(target).
//    attack if needed
class Advance : public Order {
public:
    Advance();
    Advance(Player* player, Territory* fromTerritory, Territory* toTerritory,int numOfArmies);
    Advance(const Advance& toCopy);
    ~Advance();
    Advance& operator=(const Advance& rightSide);

    virtual bool validate();
    virtual void execute();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& out, const Advance& toOutput);

private:
    Territory* fromTerritory;
    Territory* toTerritory;
    int numOfArmies;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


//bomb: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories.
class Bomb : public Order {
public:
    Bomb();
    Bomb(Player* player, Territory* toTerritory);
    Bomb(const Bomb& toCopy);
    ~Bomb();
    Bomb& operator=(const Bomb& rightSide);

    virtual bool validate();
    virtual void execute();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& out, const Bomb& toOutput);

private:
    Territory* toTerritory;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


//blockade: triple the number of armies on one of the current player’s territories and make it a neutral territory
class Blockade : public Order {
public:
    Blockade();
    Blockade(Player* player, Territory* TerritoryBlocked);
    Blockade(const Blockade& toCopy);
    ~Blockade();
    Blockade& operator=(const Blockade& rightSide);

    virtual bool validate();
    virtual void execute();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& out, const Blockade& toOutput);

private:
    Territory* TerritoryBlocked;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


//airlift: advance some armies from one of the current player’s territories to any another territory
class Airlift : public Order {
public:
    Airlift();
    Airlift(Player* player, Territory* fromTerritory, Territory* toTerritory,int numOfArmies);
    Airlift(const Airlift& toCopy);
    ~Airlift();
    Airlift& operator=(const Airlift& rightSide);

    friend std::ostream& operator<<(std::ostream& out, const Airlift& toOutput);

    virtual bool validate();
    virtual void execute();
    std::string getType();

private:
    Territory* fromTerritory;
    Territory* toTerritory;
    int numOfArmies;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


//negotiate(diplomacy): prevent attacks between the current player and another player until the end of the turn.
class Negotiate : public Order {
public:
    Negotiate();
    Negotiate(Player* player1, Player* player2);
    Negotiate(const Negotiate& toCopy);
    ~Negotiate();
    Negotiate& operator=(const Negotiate& rightSide);

    virtual bool validate();
    virtual void execute();
    std::string getType();

    friend std::ostream& operator<<(std::ostream& out, const Negotiate& toOutput);

private:
    Player* player2;
    virtual std::ostream& doPrint(std::ostream& out) const;
};


