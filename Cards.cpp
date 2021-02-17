//
// Created by Bowen Yang on 2021/1/30.
//
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <random>
#include <iterator>
#include <map>
#include "Cards.h"


using namespace std;

Card::Card(CardType type, std::string name, int number_of_army, int number_of_movement, int buildCity, int elixers, int
kill_army, int fly_ability, int victory_point, int build_ability, int move_ability, int immune_to_attack, bool
           one_vp_for_night, bool one_vp_for_cursed, bool one_vp_for_arcane, bool one_vp_for_ancient,
           bool one_vp_for_dire, bool
           one_vp_for_forest, bool one_vp_3_coins, bool one_vp_for_fly, bool three_vp_have_two_mountain, bool
           three_vp_four_noble, bool OR_CARD, int money) : type(type), name(name),
                                                           number_of_army
                                                                   (number_of_army),
                                                           number_of_movement(number_of_movement), buildCity(buildCity),
                                                           elixers(elixers), kill_army(kill_army),
                                                           fly_ability(fly_ability), victory_point(victory_point),
                                                           build_ability(build_ability), move_ability
                                                                   (move_ability), immune_to_attack(immune_to_attack),
                                                           one_vp_for_night(one_vp_for_night), one_vp_for_cursed
                                                                   (one_vp_for_cursed),
                                                           one_vp_for_arcane(one_vp_for_arcane),
                                                           one_vp_for_ancient(one_vp_for_ancient),
                                                           one_vp_for_dire(one_vp_for_dire),
                                                           one_vp_for_forest(one_vp_for_forest),
                                                           one_vp_3_coins(one_vp_3_coins),
                                                           one_vp_for_fly(one_vp_for_fly),
                                                           three_vp_have_two_mountain(three_vp_have_two_mountain),
                                                           three_vp_four_noble
                                                                   (three_vp_four_noble), OR_CARD(OR_CARD),
                                                           money(money) {
//    std::cout<<"card: "+name+" is created!"<<endl;
}

Card::Card(const Card &card) {
    type = card.type;
    name = card.name;
    number_of_army = card.number_of_army;
    number_of_movement = card.number_of_movement;
    buildCity = card.buildCity;
    elixers = card.elixers;
    kill_army = card.kill_army;
    fly_ability = card.fly_ability;
    victory_point = card.victory_point;
    build_ability = card.build_ability;
    move_ability = card.move_ability;
    immune_to_attack = card.immune_to_attack;
    one_vp_for_night = card.one_vp_for_night;
    one_vp_for_cursed = card.one_vp_for_cursed;
    one_vp_for_arcane = card.one_vp_for_arcane;
    one_vp_for_ancient = card.one_vp_for_ancient;
    one_vp_for_dire = card.one_vp_for_dire;
    one_vp_for_forest = card.one_vp_for_forest;
    one_vp_3_coins = card.one_vp_3_coins;
    one_vp_for_fly = card.one_vp_for_fly;
    three_vp_have_two_mountain = card.three_vp_have_two_mountain;
    three_vp_four_noble = card.three_vp_four_noble;
    OR_CARD = card.OR_CARD;
    money = card.money;
}

//to string method
std::ostream &operator<<(std::ostream &output, const Card &card) {
    output << "card name: " + card.name << endl;
    output << "Action: " << endl;
    if (card.number_of_army > 0) {
        output << "can build army: " << card.number_of_army << endl;
    }
    if (card.number_of_movement > 0) {
        output << "can move: " << card.number_of_movement << endl;
    }
    if (card.buildCity > 0) {
        output << "build one city" << endl;
    }
    if (card.kill_army > 0) {
        output << "can kill army: " << card.kill_army << endl;
    }

    output << "Goods: " << endl;
    if (card.elixers > 0) {
        output << "elixers: " << card.elixers << endl;
    }

    if (card.fly_ability > 0) {
        output << "wings" << endl;
    }
    if (card.victory_point > 0) {
        output << "has victory point: " << card.victory_point << endl;
    }
    if (card.build_ability > 0) {
        output << "build one more army when build army" << endl;
    }
    if (card.move_ability > 0) {
        output << "one more movement when move" << endl;
    }
    if (card.immune_to_attack > 0) {
        output << "immune to attack" << endl;
    }
    if (card.one_vp_for_night) {
        output << "one victory point for each night card" << endl;
    }
    if (card.one_vp_for_cursed) {
        output << "one victory point for each cursed card" << endl;
    }
    if (card.one_vp_for_arcane) {
        output << "one victory point for each arcane card" << endl;
    }
    if (card.one_vp_for_ancient) {
        output << "one victory point for each ancient card" << endl;
    }
    if (card.one_vp_for_dire) {
        output << "one victory point for dire night card" << endl;
    }
    if (card.one_vp_for_forest) {
        output << "one victory point for each forest card" << endl;
    }
    if (card.one_vp_3_coins) {
        output << "one victory point for every 3 coins" << endl;
    }
    if (card.one_vp_for_fly) {
        output << "one victory point for each wing" << endl;
    }
    if (card.OR_CARD) {
        output << "This is a card with OR, you need to choose the action later." << endl;
    }
    if (card.money != 0) {
        output << "This card have 2 more coins" << endl;
    }
    if (card.three_vp_have_two_mountain) {
        output << "+3vp if you have two Mountain cards" << endl;
    }
    if (card.three_vp_four_noble) {
        output << "Three noble cards=4vp" << endl;
    }
//    output<<endl;
    return output;
}

Card::Card() {
    type = emptyKind;
    name = "none";
    number_of_army = 0;
    number_of_movement = 0;
    buildCity = 0;
    elixers = 0;
    kill_army = 0;
    fly_ability = 0;
    victory_point = 0;
    build_ability = 0;
    move_ability = 0;
    immune_to_attack = 0;
    one_vp_for_night = false;
    one_vp_for_cursed = false;
    one_vp_for_arcane = false;
    one_vp_for_ancient = false;
    one_vp_for_dire = false;
    one_vp_for_forest = false;
    one_vp_3_coins = false;
    one_vp_for_fly = false;
    three_vp_four_noble = false;
    three_vp_have_two_mountain = false;
    OR_CARD = false;
    money = 0;
}

//为啥返回ref
Card &Card::operator=(const Card &card) {
    this->type = card.type;
    this->name = card.name;
    this->number_of_army = card.number_of_army;
    this->number_of_movement = card.number_of_movement;
    this->buildCity = card.buildCity;
    this->elixers = card.elixers;
    this->kill_army = card.kill_army;
    this->fly_ability = card.fly_ability;
    this->victory_point = card.victory_point;
    this->build_ability = card.build_ability;
    this->move_ability = card.move_ability;
    this->immune_to_attack = card.immune_to_attack;
    this->one_vp_for_night = card.one_vp_for_night;
    this->one_vp_for_cursed = card.one_vp_for_cursed;
    this->one_vp_for_arcane = card.one_vp_for_arcane;
    this->one_vp_for_ancient = card.one_vp_for_ancient;
    this->one_vp_for_dire = card.one_vp_for_dire;
    this->one_vp_for_forest = card.one_vp_for_forest;
    this->one_vp_3_coins = card.one_vp_3_coins;
    this->one_vp_for_fly = card.one_vp_for_fly;
    this->three_vp_have_two_mountain = card.three_vp_have_two_mountain;
    this->three_vp_four_noble = card.three_vp_four_noble;
    this->OR_CARD = card.OR_CARD;
    this->money = card.money;

    return *this;
}

CardType Card::getType() const {
    return type;
}

void Card::setType(CardType type) {
    Card::type = type;
}

const string &Card::getName() const {
    return name;
}

void Card::setName(const string &name) {
    Card::name = name;
}

int Card::getNumberOfArmy() const {
    return number_of_army;
}

void Card::setNumberOfArmy(int numberOfArmy) {
    number_of_army = numberOfArmy;
}

int Card::getNumberOfMovement() const {
    return number_of_movement;
}

void Card::setNumberOfMovement(int numberOfMovement) {
    number_of_movement = numberOfMovement;
}

int Card::getBuildCity() const {
    return buildCity;
}

void Card::setBuildCity(int buildCity) {
    Card::buildCity = buildCity;
}

int Card::getKillArmy() const {
    return kill_army;
}

void Card::setKillArmy(int killArmy) {
    kill_army = killArmy;
}

int Card::getElixers() const {
    return elixers;
}

void Card::setElixers(int elixers) {
    Card::elixers = elixers;
}

int Card::getFlyAbility() const {
    return fly_ability;
}

void Card::setFlyAbility(int flyAbility) {
    fly_ability = flyAbility;
}

int Card::getVictoryPoint() const {
    return victory_point;
}

void Card::setVictoryPoint(int victoryPoint) {
    victory_point = victoryPoint;
}

int Card::getBuildAbility() const {
    return build_ability;
}

void Card::setBuildAbility(int buildAbility) {
    build_ability = buildAbility;
}

int Card::getMoveAbility() const {
    return move_ability;
}

void Card::setMoveAbility(int moveAbility) {
    move_ability = moveAbility;
}

int Card::getImmuneToAttack() const {
    return immune_to_attack;
}

void Card::setImmuneToAttack(int immuneToAttack) {
    immune_to_attack = immuneToAttack;
}

bool Card::isOneVpForNight() const {
    return one_vp_for_night;
}

void Card::setOneVpForNight(bool oneVpForNight) {
    one_vp_for_night = oneVpForNight;
}

bool Card::isOneVpForCursed() const {
    return one_vp_for_cursed;
}

void Card::setOneVpForCursed(bool oneVpForCursed) {
    one_vp_for_cursed = oneVpForCursed;
}

bool Card::isOneVpForArcane() const {
    return one_vp_for_arcane;
}

void Card::setOneVpForArcane(bool oneVpForArcane) {
    one_vp_for_arcane = oneVpForArcane;
}

bool Card::isOneVpForAncient() const {
    return one_vp_for_ancient;
}

void Card::setOneVpForAncient(bool oneVpForAncient) {
    one_vp_for_ancient = oneVpForAncient;
}

bool Card::isOneVpForDire() const {
    return one_vp_for_dire;
}

void Card::setOneVpForDire(bool oneVpForDire) {
    one_vp_for_dire = oneVpForDire;
}

bool Card::isOneVpForForest() const {
    return one_vp_for_forest;
}

void Card::setOneVpForForest(bool oneVpForForest) {
    one_vp_for_forest = oneVpForForest;
}

bool Card::isOneVp3Coins() const {
    return one_vp_3_coins;
}

void Card::setOneVp3Coins(bool oneVp3Coins) {
    one_vp_3_coins = oneVp3Coins;
}

bool Card::isOneVpForFly() const {
    return one_vp_for_fly;
}

void Card::setOneVpForFly(bool oneVpForFly) {
    one_vp_for_fly = oneVpForFly;
}

bool Card::isThreeVpHaveTwoMountain() const {
    return three_vp_have_two_mountain;
}

void Card::setThreeVpHaveTwoMountain(bool threeVpHaveTwoMountain) {
    three_vp_have_two_mountain = threeVpHaveTwoMountain;
}

bool Card::isThreeVpFourNoble() const {
    return three_vp_four_noble;
}

void Card::setThreeVpFourNoble(bool threeVpFourNoble) {
    three_vp_four_noble = threeVpFourNoble;
}

bool Card::isOrCard() const {
    return OR_CARD;
}

void Card::setOrCard(bool orCard) {
    OR_CARD = orCard;
}

int Card::getMoney() const {
    return money;
}

void Card::setMoney(int money) {
    Card::money = money;
}

Deck::Deck() {
    cout << "default 2 players deck:" << endl;
    deckVector = new std::vector<Card*>();
    //27 for two players:
    //ancient
    deckVector->emplace_back(new Card(ancient, "Ancient Phoenix", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                 false, false, false, false, false, false, 0));
    deckVector->emplace_back(
            new Card(ancient, "Ancient Sage", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, true, false,
                 false, false, false, false, false, false, 0));
    deckVector->emplace_back(
            new Card(ancient, "Ancient Tree Spirit", 4, 0, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                 false,
                 false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(ancient, "Ancient Woods", 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    //cursed
    deckVector->emplace_back(new Card(cursed, "Cursed Banshee", 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(cursed, "Cursed Gargoyles", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(cursed, "Cursed King", 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, true, 0));
    deckVector->emplace_back(new Card(cursed, "Cursed Mausoleum", 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(cursed, "Cursed Tower", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, true, false, false, false, 0));
    //dire
    deckVector->emplace_back(new Card(dire, "Dire Dragon", 3, 0, 0, 0, 1, 1, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(dire, "Dire Eye", 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(dire, "Dire Giant", 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(dire, "Dire Goblin", 0, 5, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(dire, "Dire Ogre", 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, true, false, false, false, false, 0));
    //forest
    deckVector->emplace_back(new Card(forest, "Forest Elf", 3, 2, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, true, 0));
    deckVector->emplace_back(new Card(forest, "Forest Gnome", 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(forest, "Forest Pixie", 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(forest, "Forest Tree Town", 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    //empty kind
    deckVector->emplace_back(new Card(emptyKind, "Graveyard", 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, true, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(emptyKind, "Lake", 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  true, false, false, false, false, true, 0));
    deckVector->emplace_back(new Card(emptyKind, "Stronghold", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  true,
                                  false, false, false, false, false, false, 0));
    //Night
    deckVector->emplace_back(new Card(night, "Night Hydra", 0, 5, 0, 0, 1, 0, 0, 1, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(night, "Night Village", 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(night, "Night Wizard", 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, true, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    //noble
    deckVector->emplace_back(new Card(noble, "Noble Hills", 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, true, false, 0));
    deckVector->emplace_back(new Card(noble, "Noble Knight", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));
    deckVector->emplace_back(new Card(noble, "Noble Unicorn", 1, 4, 0, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                                  false,
                                  false, false, false, false, false, false, 0));

    // using built-in random generator:
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deckVector->begin(), deckVector->end(), g);
}
Deck::Deck(int number_of_player) {
    deckVector = new std::vector<Card*>();
    if (number_of_player == 2) {
        cout << "Two players deck:" << endl;
        //27 for two players:
        //ancient
        deckVector->emplace_back(
                new Card(ancient, "Ancient Phoenix", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Sage", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, true, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Tree Spirit", 4, 0, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Woods", 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //cursed
        deckVector->emplace_back(
                new Card(cursed, "Cursed Banshee", 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Gargoyles", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed King", 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Mausoleum", 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed Tower", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, true, false, false, false, 0));
        //dire
        deckVector->emplace_back(new Card(dire, "Dire Dragon", 3, 0, 0, 0, 1, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Eye", 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Giant", 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Goblin", 0, 5, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Ogre", 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, true, false, false, false, false, 0));
        //forest
        deckVector->emplace_back(new Card(forest, "Forest Elf", 3, 2, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(forest, "Forest Gnome", 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(forest, "Forest Pixie", 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(forest, "Forest Tree Town", 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //empty kind
        deckVector->emplace_back(new Card(emptyKind, "Graveyard", 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, true, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(emptyKind, "Lake", 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      true, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(emptyKind, "Stronghold", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      true,
                                      false, false, false, false, false, false, 0));
        //Night
        deckVector->emplace_back(new Card(night, "Night Hydra", 0, 5, 0, 0, 1, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Village", 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Wizard", 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, true, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        //noble
        deckVector->emplace_back(new Card(noble, "Noble Hills", 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, true, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Knight", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Unicorn", 1, 4, 0, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
    }
    if (number_of_player == 3) {
        cout << "Three players deck:" << endl;
        //27 for two players:
        //ancient
        deckVector->emplace_back(
                new Card(ancient, "Ancient Phoenix", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Sage", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, true, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Tree Spirit", 4, 0, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Woods", 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //cursed
        deckVector->emplace_back(
                new Card(cursed, "Cursed Banshee", 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Gargoyles", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed King", 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Mausoleum", 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed Tower", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, true, false, false, false, 0));
        //dire
        deckVector->emplace_back(new Card(dire, "Dire Dragon", 3, 0, 0, 0, 1, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Eye", 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Giant", 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Goblin", 0, 5, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Ogre", 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, true, false, false, false, false, 0));
        //forest
        deckVector->emplace_back(new Card(forest, "Forest Elf", 3, 2, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(forest, "Forest Gnome", 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(forest, "Forest Pixie", 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(forest, "Forest Tree Town", 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //empty kind
        deckVector->emplace_back(new Card(emptyKind, "Graveyard", 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, true, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(emptyKind, "Lake", 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      true, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(emptyKind, "Stronghold", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      true,
                                      false, false, false, false, false, false, 0));
        //Night
        deckVector->emplace_back(new Card(night, "Night Hydra", 0, 5, 0, 0, 1, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Village", 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Wizard", 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, true, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        //noble
        deckVector->emplace_back(new Card(noble, "Noble Hills", 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, true, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Knight", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Unicorn", 1, 4, 0, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        //5 more for three players
        deckVector->emplace_back(
                new Card(arcane, "Arcane Sphinx", 3, 4, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, true, 0));

        deckVector->emplace_back(
                new Card(arcane, "Arcane Manticore", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));

        deckVector->emplace_back(
                new Card(arcane, "Arcane Temple", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, true, false, false,
                     false, false, false, false, false, false, 0));

        deckVector->emplace_back(
                new Card(mountain, "Mountain Dwarf", 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, true, false, false, 0));

        deckVector->emplace_back(
                new Card(mountain, "Mountain Treasury", 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 1));


    }
    if (number_of_player == 4) {
        cout << "Four players deck:" << endl;
        //27 for two players:
        //ancient
        deckVector->emplace_back(
                new Card(ancient, "Ancient Phoenix", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Sage", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, true, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Tree Spirit", 4, 0, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(ancient, "Ancient Woods", 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //cursed
        deckVector->emplace_back(
                new Card(cursed, "Cursed Banshee", 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Gargoyles", 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed King", 3, 4, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(
                new Card(cursed, "Cursed Mausoleum", 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(cursed, "Cursed Tower", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, true, false, false, false, 0));
        //dire
        deckVector->emplace_back(new Card(dire, "Dire Dragon", 3, 0, 0, 0, 1, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Eye", 4, 0, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Giant", 3, 0, 0, 0, 1, 0, 0, 0, 0, 1, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Goblin", 0, 5, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(dire, "Dire Ogre", 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, true, false, false, false, false, 0));
        //forest
        deckVector->emplace_back(new Card(forest, "Forest Elf", 3, 2, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(forest, "Forest Gnome", 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(forest, "Forest Pixie", 0, 4, 0, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(forest, "Forest Tree Town", 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 0));
        //empty kind
        deckVector->emplace_back(new Card(emptyKind, "Graveyard", 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, true, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(emptyKind, "Lake", 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      true, false, false, false, false, true, 0));
        deckVector->emplace_back(new Card(emptyKind, "Stronghold", 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      true,
                                      false, false, false, false, false, false, 0));
        //Night
        deckVector->emplace_back(new Card(night, "Night Hydra", 0, 5, 0, 0, 1, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Village", 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(night, "Night Wizard", 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, true, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        //noble
        deckVector->emplace_back(new Card(noble, "Noble Hills", 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, true, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Knight", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        deckVector->emplace_back(new Card(noble, "Noble Unicorn", 1, 4, 0, 0, 0, 0, 0, 0, 1, 0, false, false, false, false,
                                      false,
                                      false, false, false, false, false, false, 0));
        //5 more for three players
        deckVector->emplace_back(
                new Card(arcane, "Arcane Sphinx", 3, 4, 0, 0, 0, 1, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, true, 0));
        deckVector->emplace_back(
                new Card(arcane, "Arcane Manticore", 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(arcane, "Arcane Temple", 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, false, false, true, false, false,
                     false, false, false, false, false, false, 0));
        deckVector->emplace_back(
                new Card(mountain, "Mountain Dwarf", 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, true, false, false, 0));
        deckVector->emplace_back(
                new Card(mountain, "Mountain Treasury", 0, 3, 0, 1, 0, 0, 0, 0, 0, 0, false, false, false, false,
                     false,
                     false, false, false, false, false, false, 1));
        //2 more for 4 players:
        deckVector->emplace_back(
                new Card(emptyKind, "Castle 1", 3, 0, 1, 1, 0, 0, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, true, 0));
        deckVector->emplace_back(
                new Card(emptyKind, "Castle 2", 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, false, false, false, false, false,
                     false, false, false, false, false, false, 0));
    }
    // using built-in random generator:
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deckVector->begin(), deckVector->end(), g);
}

Deck::~Deck() {
    for (unsigned i=0; i<deckVector->size(); i++) {
        delete deckVector->at(i);
        deckVector->at(i) = nullptr;
    }
    delete deckVector;
    deckVector = nullptr;
}

Deck::Deck(const Deck &deck) {
    this->deckVector = new vector<Card*>(*(deck.deckVector));
}

Deck &Deck::operator=(const Deck &deck) {
    this->deckVector = new std::vector<Card*>(*(deck.deckVector));
    return *this;
}


std::ostream &operator<<(std::ostream &output, const Deck &deck) {
    for (int i = 0; i < deck.deckVector->size(); i++) {
        output << *deck.deckVector->at(i) << endl;
    }
    return output;
}

std::vector<Card*>* Deck::getDeckVector() {
    return deckVector;
}

Card *Deck::draw() {
    if (!(getDeckVector()->empty())) {
        Card* card = getDeckVector()->back();
        getDeckVector()->pop_back();
        return card;
    } else {
        //cout<<"no more card in the Deck!"<<endl;
        Card *lastcard = new Card(emptyKind, "NoMoreCards", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, false, false, false, false,
                                  false, false,
                                  false,
                                  false, false, false, false, 0);
        return lastcard;
    }
}

Hand::Hand() {
    handVector = new std::vector<Card*>();
}


Hand::Hand(Deck *deck) {
    handVector = new std::vector<Card*>();
    //draw 6 cards in the beginning of the game
    handVector->emplace_back(deck->draw());
    handVector->emplace_back(deck->draw());
    handVector->emplace_back(deck->draw());
    handVector->emplace_back(deck->draw());
    handVector->emplace_back(deck->draw());
    handVector->emplace_back(deck->draw());
}

Hand::~Hand() {
    for (unsigned i=0; i<handVector->size(); i++) {
        delete handVector->at(i);
        handVector->at(i) = nullptr;
    }
    delete handVector;
    handVector = nullptr;
}

Hand::Hand(const Hand &hand) {
    this->handVector = new std::vector<Card*>(*(hand.handVector));
}

Hand &Hand::operator=(const Hand &hand) {
    this->handVector = new std::vector<Card*>(*(hand.handVector));
    return *this;
}

std::ostream &operator<<(std::ostream &output, const Hand &hand) {
    map<int, int> moneyMap{{0, 0},
                           {1, 1},
                           {2, 1},
                           {3, 2},
                           {4, 2},
                           {5, 3}};
    for (int i = 0; i < hand.handVector->size(); i++) {
        output << "Card " << i + 1 << " this card takes " << moneyMap[i] << " coins " << endl;
        output << *hand.handVector->at(i) << endl;
    }
    return output;
}

std::vector<Card*> *Hand::getHandVector() {
    return handVector;
}

Card *Hand::exchange(int card_number, Deck *deck) {
    for (int i = 0; i < handVector->size(); i++) {
        if (card_number - 1 == i) {
            Card* card = new Card(*handVector->at(i));

            //std::cout << **(handVector->begin() + i)<<endl;
            //delete the ptr , avoid memory leak
            delete *(handVector->begin() + i);
            *(handVector->begin() + i)= nullptr;
            handVector->erase(handVector->begin() + i);
            //draw a new card from deck
            handVector->emplace_back(deck->draw());
            return card;
        }
    }

    return nullptr;
}

