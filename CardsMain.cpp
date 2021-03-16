//
// Created by Bowen Yang on 2021/1/30.
//

#include <iostream>
#include "Cards.h"
#include "CardsMain.h"
using namespace std;

int main(){
    //deck demo
//    cout<<"original cards:"<<endl;
//    Deck d(2);
//    cout<<d<<endl;
//    cout<<"draw one card, the card is: "<<endl;
//    cout<<*d.draw()<<endl;
//    cout<<"the rest cards in the deck"<<endl;
//    cout<<d<<endl;
//    cout<<"draw one card, the card is: "<<endl;
//    cout<<*d.draw()<<endl;
//    cout<<"the rest cards in the deck"<<endl;
//    cout<<d<<endl;
//    cout<<"draw one card, the card is: "<<endl;
//    cout<<*d.draw()<<endl;

//hand demo
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

    return 0;
}
