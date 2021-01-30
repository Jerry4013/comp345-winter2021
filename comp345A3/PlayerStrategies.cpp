//
// Created by Luojia yan on 2020-12-02.
//
#include "PlayerStrategies.h"


PlayerStrategies::PlayerStrategies(){
    PlayerStatus="UNKNOWN";
}
void HumanPlayerStraregies::SetPlayerStatus(Player* player){
    player->Playerstrategies->PlayerStatus = "Human";
    cout << player->getPlayerName() << "'s status becoming Human";
}
void BenevolentPlayerStraregies::SetPlayerStatus(Player* player){
    player->Playerstrategies->PlayerStatus = "Benevolent";
    cout << player->getPlayerName() << "'s status becoming Benevolent";
}
void AggressivePlayerStraregies::SetPlayerStatus(Player* player){
    player->Playerstrategies->PlayerStatus = "Aggressive";
    cout << player->getPlayerName() << "'s status becoming Aggressive";
}
void NeutralPlayerStraregies::SetPlayerStatus(Player* player){
    player->Playerstrategies->PlayerStatus = "Neutral";
    cout << player->getPlayerName() << "'s status becoming Neutral";
}




string HumanPlayerStraregies::GetPlayerStatus(Player* player){
    cout <<player->getPlayerName()<< " type is :  "<<player->Playerstrategies->PlayerStatus;
    return player->Playerstrategies->PlayerStatus;

}
string BenevolentPlayerStraregies::GetPlayerStatus(Player* player){
    cout <<player->getPlayerName()<< " type is :  "<<player->Playerstrategies->PlayerStatus;
    return player->Playerstrategies->PlayerStatus;

}
string AggressivePlayerStraregies::GetPlayerStatus(Player* player){
    cout <<player->getPlayerName()<< " type is :  "<<player->Playerstrategies->PlayerStatus;
    return player->Playerstrategies->PlayerStatus;
}
string NeutralPlayerStraregies::GetPlayerStatus(Player* player){
    cout <<player->getPlayerName()<< " type is :  "<<player->Playerstrategies->PlayerStatus;
    return player->Playerstrategies->PlayerStatus;
}

