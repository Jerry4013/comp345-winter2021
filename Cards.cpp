//
// Created by Bowen Yang on 2021/1/30.
//

#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <random>
#include <iterator>
#include <iomanip>
#include "Cards.h"

using namespace std;

const vector<int> Hand::CARD_COSTS = {0, 1, 1, 2, 2, 3};

ostream &operator<<(ostream &output, const Action &action) {
    switch (action.actionType) {
        case placeArmy:
            output << "place " << action.amount << " armies";
            break;
        case moveArmy:
            output << "move " << action.amount << " armies";
            break;
        case buildCity:
            output << "build a city";
            break;
        case destroyArmy:
            output << "destroy " << action.amount << " armies";
            break;
    }
    return output;
}

Card::Card() {
    cardType = emptyKind;
    name = "none";
    isAndCard = false;
    isOrCard = false;
}

Card::Card(CardType type, string name, vector<Ability> abilities, vector<Action> actions, bool isAndCard, bool isOrCard) {
    this->cardType = type;
    this->name = name;
    this->abilities = abilities;
    this->actions = actions;
    this->isAndCard = isAndCard;
    this->isOrCard = isOrCard;
}

Card::Card(const Card &card) {
    cardType = card.cardType;
    name = card.name;
    abilities = card.abilities;
    actions = card.actions;
    isAndCard = card.isAndCard;
    isOrCard = card.isOrCard;
}

std::ostream &operator<<(std::ostream &output, const Card &card) {
    // TODO
    output << "card name: " + card.name << endl;
    if (card.abilities.size() == 2) {

    } else {

    }
    output << "Action: ";
    if (!card.isAndCard && !card.isOrCard) {
        Action action = card.actions[0];
        // output << action.actionType;

    }


    return output;
}

Card &Card::operator=(const Card &card) {
    cardType = card.cardType;
    name = card.name;
    abilities = card.abilities;
    actions = card.actions;
    isAndCard = card.isAndCard;
    isOrCard = card.isOrCard;
    return *this;
}

CardType Card::getType() const {
    return cardType;
}

void Card::setType(CardType newCardType) {
    cardType = newCardType;
}

string Card::getName() const {
    return name;
}

void Card::setName(string& newName) {
    name = newName;
}

Card::~Card() {
    // did not use new in the constructor.
}

vector<Ability> Card::getAbilities() {
    return abilities;
}

vector<Action> Card::getActions() {
    return actions;
}

bool Card::getAnd() {
    return isAndCard;
}

bool Card::getOr() {
    return isOrCard;
}

Deck::Deck() {
    cout << "default 2 players deck:" << endl;
    initializeDeckOfTwoPlayers();
    shuffleDeck();
}

void Deck::initializeDeckOfTwoPlayers() {
    //27 for two players:
    //ancient
    cards.emplace_back(new Card(ancient, "Ancient Phoenix",
                                {{flying, 1, nullVpType, emptyKind}},
                                {{moveArmy, 5}}, false, false));
    cards.emplace_back(new Card(ancient, "Ancient Tree Spirit",
                                {{elixir, 3, nullVpType, emptyKind}},
                                {{placeArmy, 4}}, false, false));
    cards.emplace_back(new Card(ancient, "Ancient Woods",
                                {{army, 1, nullVpType, emptyKind}},
                                {{buildCity, 1}, {placeArmy, 1}},
                                true, false));
    cards.emplace_back(new Card(ancient, "Ancient Sage",
                                {{VP, 1, cardType, ancient}},
                                {{moveArmy, 3}}, false, false));

    //cursed
    cards.emplace_back(new Card(cursed, "Cursed Banshee",
                                {{elixir, 2, nullVpType, emptyKind}},
                                {{moveArmy, 6}}, false, false));
    cards.emplace_back(new Card(cursed, "Cursed Gargoyles",
                                {{flying, 1, nullVpType, emptyKind}},
                                {{moveArmy, 5}}, false, false));
    cards.emplace_back(new Card(cursed, "Cursed King",
                                {{elixir, 1, nullVpType, emptyKind}},
                                {{placeArmy, 3}, {moveArmy, 4}},
                                false, true));
    cards.emplace_back(new Card(cursed, "Cursed Mausoleum",
                                {{moving, 1, nullVpType, emptyKind}},
                                {{buildCity, 1}}, false, false));
    cards.emplace_back(new Card(cursed, "Cursed Tower",
                                {{VP, 1, vpPerFlying, emptyKind}},
                                {{buildCity, 1}}, false, false));
    cards.emplace_back(new Card(emptyKind, "Graveyard",
                                {{VP, 1, cardType, cursed}},
                                {{placeArmy, 2}}, false, false));

    //dire
    cards.emplace_back(new Card(dire, "Dire Dragon",
                                {{flying, 1, nullVpType, emptyKind}},
                                {{placeArmy, 3}, {destroyArmy, 1}},
                                true, false));
    cards.emplace_back(new Card(dire, "Dire Giant",
                                {{immuneAttack, 1, nullVpType, emptyKind}},
                                {{placeArmy, 3}, {destroyArmy, 1}},
                                true, false));
    cards.emplace_back(new Card(dire, "Dire Eye",
                                {{flying, 1, nullVpType, emptyKind}},
                                {{placeArmy, 4}}, false, false));
    cards.emplace_back(new Card(dire, "Dire Goblin",
                                {{elixir, 1, nullVpType, emptyKind}},
                                {{moveArmy, 5}}, false, false));
    cards.emplace_back(new Card(dire, "Dire Ogre",
                                {{VP, 1, coinsLeft, emptyKind}},
                                {{moveArmy, 2}}, false, false));
    cards.emplace_back(new Card(emptyKind, "Stronghold",
                                {{VP, 1, cardType, dire}},
                                {{buildCity, 1}}, false, false));

    //forest
    cards.emplace_back(new Card(emptyKind, "Lake",
                                {{VP, 1, cardType, forest}},
                                {{placeArmy, 2}, {moveArmy, 3}},
                                false, true));
    cards.emplace_back(new Card(forest, "Forest Elf",
                                {{army, 1, nullVpType, emptyKind}},
                                {{placeArmy, 3}, {moveArmy, 2}},
                                false, true));
    cards.emplace_back(new Card(forest, "Forest Gnome",
                                {{elixir, 3, nullVpType, emptyKind}},
                                {{moveArmy, 2}},
                                false, false));
    cards.emplace_back(new Card(forest, "Forest Tree Town",
                                {{moving, 1, nullVpType, emptyKind}},
                                {{buildCity, 1}}, false, false));
    cards.emplace_back(new Card(forest, "Forest Pixie",
                                {{army, 1, nullVpType, emptyKind}},
                                {{moveArmy, 4}},
                                false, false));

    //noble
    cards.emplace_back(new Card(noble, "Noble Hills",
                                {{VP, 4, cardSet, noble}},
                                {{placeArmy, 3}},
                                false, false));
    cards.emplace_back(new Card(noble, "Noble Knight",
                                {{moving, 1, nullVpType, emptyKind}},
                                {{placeArmy, 4}, {destroyArmy, 1}},
                                true, false));
    cards.emplace_back(new Card(noble, "Noble Unicorn",
                                {{moving, 1, nullVpType, emptyKind}},
                                {{moveArmy, 4}, {placeArmy, 1}},
                                true, false));

    //Night
    cards.emplace_back(new Card(night, "Night Hydra",
                                {{army, 1, nullVpType, emptyKind}},
                                {{moveArmy, 5}, {destroyArmy, 1}},
                                true, false));
    cards.emplace_back(new Card(night, "Night Village",
                                {{army, 1, nullVpType, emptyKind}},
                                {{buildCity, 1}}, false, false));
    cards.emplace_back(new Card(night, "Night Wizard",
                                {{VP, 1, cardType, night}},
                                {{placeArmy, 3}, {destroyArmy, 1}},
                                true, false));
}

Deck::Deck(int numberOfPlayers) {
    if (numberOfPlayers >= 2) {
        initializeDeckOfTwoPlayers();
    }
    if (numberOfPlayers >= 3) {
        //32 for two players, 5 more for three players
        // arcane
        cards.emplace_back(new Card(arcane, "Arcane Sphinx",
                                    {{flying, 1, nullVpType, emptyKind}},
                                    {{placeArmy, 3}, {moveArmy, 4}},
                                    false, true));
        cards.emplace_back(new Card(arcane, "Arcane Manticore",
                                    {{moving, 1, nullVpType, emptyKind}},
                                    {{placeArmy, 4}, {destroyArmy, 1}},
                                    true, false));
        cards.emplace_back(new Card(arcane, "Arcane Temple",
                                    {{VP, 1, cardType, arcane}},
                                    {{moveArmy, 3}}, false, false));

        // mountain
        cards.emplace_back(new Card(mountain, "Mountain Dwarf",
                                    {{VP, 3, cardSet, mountain}},
                                    {{placeArmy, 2}, {destroyArmy, 1}},
                                    true, false));
        cards.emplace_back(new Card(mountain, "Mountain Treasury",
                                    {{elixir, 1, nullVpType, emptyKind},
                                     {gainCoins, 2}},
                                    {{moveArmy, 3}},
                                    false, false));
    }
    if (numberOfPlayers == 4) {
        //34 for two players, 2 more for 4 players:
        cards.emplace_back(new Card(emptyKind, "Castle 1",
                                    {{elixir, 1, nullVpType, emptyKind}},
                                    {{placeArmy, 3}, {buildCity, 1}},
                                    false, true));
        cards.emplace_back(new Card(emptyKind, "Castle 2",
                                    {{elixir, 1, nullVpType, emptyKind}},
                                    {{moveArmy, 3}, {buildCity, 1}},
                                    true, false));
    }
    shuffleDeck();
}

Deck::~Deck() {
    for (auto & card : cards) {
        delete card;
        card = nullptr;
    }
}

Deck::Deck(const Deck &deck) {
    for (auto & card : deck.cards) {
        cards.emplace_back(new Card(*card));
    }
}

Deck &Deck::operator=(const Deck &deck) {
    cards.clear();
    for (auto & card : deck.cards) {
        cards.emplace_back(new Card(*card));
    }
    return *this;
}


ostream &operator<<(std::ostream &output, const Deck &deck) {
    int size = deck.cards.size();
    output << "The top 3 cards on the deck is:" << endl;
    for (int i = 0; i < 3; ++i) {
        output << deck.cards[size - 1 - i]->getName() << ", ";
    }
    return output;
}

vector<Card*> Deck::getCards() {
    return cards;
}

Card* Deck::draw() {
    Card* card;
    if (!cards.empty()) {
        card = cards.back();
    } else {
        card = nullptr;
    }
    cards.pop_back();
    return card;
}

void Deck::shuffleDeck() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

Hand::Hand() {
    for (int i = 0; i < 6; ++i) {
        handCards.emplace_back(new Card());
    }
}

Hand::Hand(Deck *deck) {
    for (int i = 0; i < 6; ++i) {
        handCards.emplace_back(deck->draw());
    }
}

Hand::~Hand() {
    for (auto & card : handCards) {
        delete card;
        card = nullptr;
    }
}

Hand::Hand(const Hand &hand) {
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
    }
}

Hand &Hand::operator=(const Hand &hand) {
    handCards.clear();
    for (auto & card : hand.handCards) {
        handCards.emplace_back(new Card(*card));
    }
    return *this;
}

std::ostream &operator<<(ostream &output, const Hand &hand) {
    output << "The six cards:" << endl;
    output << "Cost:";
    for (int cost : Hand::CARD_COSTS) {
        output << setw(17) <<  to_string(cost) + "        ";
    }
    output << endl;
    output << "Card:";
    for (auto & card : hand.handCards) {
        output << setw(17) << card->getName();
    }
    output << "\n" << endl;
    return output;
}

vector<Card*> Hand::getHandCards() {
    return handCards;
}

Card *Hand::exchange(int cardNumber, Deck *deck) {
    Card* card = handCards[cardNumber - 1];
    handCards.erase(handCards.begin() + cardNumber - 1);
    handCards.emplace_back(deck->draw());
    return card;
}

