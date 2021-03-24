//
// Created by Bowen Yang on 2021/1/30.
//

#include <iostream>
#include "Cards.h"
#include "CardsMain.h"
using namespace std;

int cards::main(){

    Deck* deck = new Deck(4);
    Hand* hand = new Hand(deck);
    cout << *hand << endl;
    int n;
    cout << "please chose the card you want to pick (Enter 1 - 6): ";
    cin >> n;
    Card* c = hand->exchange(n, deck);
    cout << "picked card: " << n << endl;
    cout << *c << endl;

    cout << "rest of hand:" << endl;
    cout << *hand << endl;
    delete deck;
    delete hand;

    return 0;
}
