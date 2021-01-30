//
// Created by Liu He on 2020-11-22.
//


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Cards.h"

using namespace std;

Card::Card() {
    t = new CardType();
}

Card::Card(CardType type) {
    t = new CardType(type);

}

Card::Card(const Card &c) {
    this->t = new CardType(*(c.t));
}

void Card::play(Hand &player, Deck &deck) {
    if(*getCardType()<0 || *getCardType()>4){
        cout<<"invalid card!"<<endl;
    }
    else{
        int count=0;
        for(int i=0; i<player.getHandVector()->size(); i++){
            if(*getCardType()==*(player.getHandVector()->at(i).getCardType())){
                count++;
                switch (*getCardType()) {
                    case bomb:{
                        cout<<"play bomb"<<endl;
                        break;
                    }
                    case reinforcement:{
                        cout<<"play reinforcement"<<endl;
                        break;
                    }
                    case blockade:{
                        cout<<"play blockade"<<endl;
                        break;
                    }

                    case airlift:{
                        cout<<"play airlift"<<endl;
                        break;
                    }
                    case diplomacy:{
                        cout<<"play diplomacy"<<endl;
                        break;
                    }

                }
                player.getHandVector()->erase(player.getHandVector()->begin()+i);
                deck.getDeckVector()->push_back(Card(*getCardType()));
                break;
            }
        }
        if(count==0)
            cout<<"not found in player's hand!"<<endl;

    }
}


Card::~Card() {
    delete t;
    t = nullptr;
}

ostream &operator<<(ostream &output, const Card &c) {
    switch (*(c.t)) {
        case bomb:{
            output<<"bomb"<<endl;
            break;
        }
        case reinforcement:{
            output<<"reinforcement"<<endl;
            break;
        }
        case blockade:{
            output<<"blockade"<<endl;
            break;
        }

        case airlift:{
            output<<"airlift"<<endl;
            break;
        }
        case diplomacy:{
            output<<"diplomacy"<<endl;
            break;
        }

    }
    return output;
}
Card& Card::operator=(const Card &obj) {
    this->t = new CardType(*(obj.t));
    return *this;
}

CardType* Card::getCardType() {
    return t;
}


Deck::Deck() {
    deckVector = new std::vector<Card> ();
    deckVector->push_back(Card(bomb));
    deckVector->push_back(Card(reinforcement));
    deckVector->push_back(Card(blockade));
    deckVector->push_back(Card(airlift));
    deckVector->push_back(Card(diplomacy));
}

Deck::Deck(int num) {
    deckVector = new std::vector<Card> ();
    for(int i=0; i<num; i++){
        deckVector->push_back(Card(bomb));
        deckVector->push_back(Card(reinforcement));
        deckVector->push_back(Card(blockade));
        deckVector->push_back(Card(airlift));
        deckVector->push_back(Card(diplomacy));
    }

}

Deck::~Deck() {
    delete deckVector;
    deckVector = nullptr;
}

Deck::Deck(const Deck& obj) {
    this->deckVector = new vector<Card>(*(obj.deckVector));

}

Deck& Deck::operator=(const Deck &obj) {
    this->deckVector = new std::vector<Card>(*(obj.deckVector));
    return *this;
}

ostream &operator<<(ostream &output, const Deck &D) {
    for(int i=0; i<D.deckVector->size(); i++){
        output << *(D.deckVector->at(i).getCardType())<<" ";
    }
    return output;
}

std::vector<Card> *Deck::getDeckVector() {
    return deckVector;
}

Card Deck::draw( Hand& playerHand) {
    if(getDeckVector()->size() !=0){
        srand(time(0));
        int index = rand() % getDeckVector()->size();
        Card card = getDeckVector()->at(index);
        playerHand.getHandVector()->push_back(card);
        deckVector->erase(getDeckVector()->begin()+index);
        return card;
    }
    else
        cout<<"no more card in Deck!"<<endl;

}

//Card Deck::draw(Player& player) {
//    if(getDeckVector()->size() !=0){
//        srand(time(0));
//        int index = rand() % getDeckVector()->size();
//        Card card = getDeckVector()->at(index);
//        player.getHand.getHandVector()->push_back(card);
//        deckVector->erase(getDeckVector()->begin()+index);
//        return card;
//    }
//    else
//        cout<<"no more card in Deck!"<<endl;
//}


Hand::Hand() {
    handVector = new std::vector<Card>();
}

Hand::~Hand() {
    delete handVector;
    handVector = nullptr;
}

Hand::Hand(const Hand& obj) {
    this->handVector = new std::vector<Card>(*(obj.handVector));
}

Hand& Hand::operator=(const Hand &obj) {
    this->handVector = new std::vector<Card>(*(obj.handVector));
    return *this;
}

std::ostream &operator<<(ostream &output, const Hand &H) {
    for(int i=0; i<H.handVector->size(); i++){
        output << *(H.handVector->at(i).getCardType())<< " ";
    }
    return output;
}

std::vector<Card> *Hand::getHandVector() {
    return handVector;
}
