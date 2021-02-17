//
// Created by yhxyt on 2021/2/13.
//

#include "WholeGame.h"
#include "Cards.h"

void WholeGame::CardDemo() {
    Deck* deck =new Deck(4);
    Hand* hand=new Hand(deck);
    cout<<*hand<<endl;
    P p;
    int n=0;
    cout<<"please chose the card you want to pick: ";
    cin>>n;
    Card* c=hand->exchange(n,p,deck);
    cout<<"picked card: "<<n<<endl;
    cout<<*c<<endl;

    cout<<"rest of hand:"<<endl;
    cout<<*hand<<endl;
}

int main(){
    WholeGame* wg=new WholeGame();

    wg->CardDemo();


}


