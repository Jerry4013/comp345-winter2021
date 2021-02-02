//
// Created by Bowen Yang on 2021/1/30.
//

#include <iostream>
#include "Cards.h"
using namespace std;

int main(){
    cout<<"original cards:"<<endl;
    Deck d(4);
    cout<<d<<endl;
    cout<<"draw one card, the card is: "<<endl;
    cout<<d.draw()<<endl;
    cout<<"the rest cards in the deck"<<endl;
    cout<<d<<endl;
    cout<<"draw one card, the card is: "<<endl;
    cout<<d.draw()<<endl;
    cout<<"the rest cards in the deck"<<endl;
    cout<<d<<endl;
    cout<<"draw one card, the card is: "<<endl;
    cout<<d.draw()<<endl;
//    cout<<d.draw()<<endl;
//    cout<<d<<endl;


}
