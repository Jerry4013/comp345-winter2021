#include <iostream>
#include "Map.h"
#include "GameEngine.h"
#include "Cards.h"
#include "OrdersLists.h"
vector<Player*> PlayerList;
vector<Continent*> ContinentList;
vector<Territory*> TerritoryList;
int Mapchoose;
int NumberOfPlayersGlobal;


void HelperFunction::ReturnStatsAboutTerritory(Territory *territory) {
    cout << "Terrirtory number: "<<territory->GetTerritoryNumber()<<endl;
    cout << "Terrirtory name: "<<territory->GetTerritoryName()<<endl;
    cout << "Terrirtory troops: "<<territory->GetNumOfTroops()<<endl;
    cout << "Terrirtory Owner name: "<<territory->GetOwnererName()<<endl;
    cout << "Terrirtory Continent Number: "<<territory->GetContinentNumber()<<endl;
    cout << "Terrirtory Continent name: "<<territory->GetContinentName()<<endl;
}

int HelperFunction::ReturnNumberOfContinents() {
    for(int i =0 ; i<100;i++){
        if(ContinentNameFromMap[i]=="NONE"){
            return i;
        }
    }
}

int HelperFunction::ReturnNumberOfContries() {
    for(int i =0 ; i<100;i++){
        if(ContriesNumberFromMap[i]==0){
            return i;
        }
    }
}





void GameStart::ChooseMap(){
    cout<< "select a map from this list: " << "\n";
    cout << "1 Brasil"<< "\n";
    cout << "2 Europe"<< "\n";
    cout << "3 Greece"<< "\n";
    cout << "4 Maxico"<< "\n";
    cout << "5 Serbia"<< "\n";
    checkinput = true;
    cin >> MapNumberChoose;
    while(checkinput) {
        switch (MapNumberChoose) {
            case 1:
                cout << "you choose Brasil" << "\n";
                checkinput = false;
                loadmap->loadMap("../MapSource/brasil.map");
                break;
            case 2:
                cout << "you choose Europe" << "\n";
                loadmap->loadMap("../MapSource/europe.map");
                checkinput = false;
                break;
            case 3:
                cout << "you choose Greece" << "\n";
                loadmap->loadMap("../MapSource/greece.map");
                checkinput = false;
                break;
            case 4:
                cout << "you choose Maxico" << "\n";
                loadmap->loadMap("../MapSource/mexico.map");
                checkinput = false;
                break;
            case 5:
                cout << "you choose Serbia" << "\n";
                loadmap->loadMap("../MapSource/serbia.map");
                checkinput = false;
                break;
            default:
                cout << "Not a valid input " << "\n";
                cout << "ReEnter your input (number)" << "\n";
                cin >> MapNumberChoose;
                checkinput = true;

        }
    }
};

void GameStart::ChooseNumberOfPlayers() {
    cout<< "Choose Number of players(from 2-5): " << "\n";
    cin >> NumberOfPlayers;
    checkinput = true;
    while(checkinput) {
        switch (NumberOfPlayers) {
            case 2:
            {cout << "you choose 2 players" << "\n";
                checkinput = false;
                vector<Territory*> territoryPlayerOne;
                vector<Territory*> territoryPlayerTwo;
                PlayerStrategies* Playerstrategies1 = new PlayerStrategies();
                PlayerStrategies* Playerstrategies2= new PlayerStrategies();
                Player* playerOne = new Player("Player1",territoryPlayerOne,Playerstrategies1);
                Player* playerTwo = new Player("Player2",territoryPlayerTwo,Playerstrategies2);
                PlayerList.push_back(playerOne);
                PlayerList.push_back(playerTwo);
//                cout << "test part: "<<endl;
//                cout <<playerOne->getPlayerName()<<" territory list has size of " ;
//                cout << playerOne->getTerritoryList().size()<<endl;
//                cout <<playerTwo->getPlayerName()<<" territory list has size of " ;
//                cout << playerTwo->getTerritoryList().size()<<endl;
//                Territory* t2 = new Territory();
//                playerTwo->territoryList.push_back(t2);
//                cout <<playerTwo->getPlayerName()<<" territory list now has size of " ;
//                cout << playerTwo->getTerritoryList().size()<<endl;
//                cout << "test end "<<endl;
                cout << "Player 1 is created with empty territory" << "\n";
                cout << "Player 2 is created with empty territory" << "\n";
                NumberOfPlayersGlobal=2;
                break;}
            case 3:
            {cout << "you choose 3 players" << "\n";
                vector<Territory*> territoryPlayerOne;
                vector<Territory*> territoryPlayerTwo;
                vector<Territory*> territoryPlayerThree;
                PlayerStrategies* Playerstrategies1= new PlayerStrategies();
                PlayerStrategies* Playerstrategies2= new PlayerStrategies();
                PlayerStrategies* Playerstrategies3= new PlayerStrategies();
                Player* playerOne = new Player("Player1",territoryPlayerOne,Playerstrategies1);
                Player* playerTwo = new Player("Player2",territoryPlayerTwo,Playerstrategies2);
                Player* playerThree = new Player("Player3",territoryPlayerThree,Playerstrategies3);
                PlayerList.push_back(playerOne);
                cout << "Player 1 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerTwo);
                cout << "Player 2 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerThree);
                cout << "Player 3 is created with empty card deck and empty territory" << "\n";
                checkinput = false;
                NumberOfPlayersGlobal=3;
                break;}
            case 4:
            {cout << "you choose 4 players" << "\n";
                std::vector<Territory*> territoryPlayerOne;
                std::vector<Territory*> territoryPlayerTwo;
                std::vector<Territory*> territoryPlayerThree;
                std::vector<Territory*> territoryPlayerFour;
                PlayerStrategies* Playerstrategies1= new PlayerStrategies();
                PlayerStrategies* Playerstrategies2= new PlayerStrategies();
                PlayerStrategies* Playerstrategies3= new PlayerStrategies();
                PlayerStrategies* Playerstrategies4= new PlayerStrategies();
                Player* playerOne = new Player("Player1",territoryPlayerOne,Playerstrategies1);
                Player* playerTwo = new Player("Player2",territoryPlayerTwo,Playerstrategies2);
                Player* playerThree = new Player("Player3",territoryPlayerThree,Playerstrategies3);
                Player* playerFour = new Player("Player4",territoryPlayerFour,Playerstrategies4);
                PlayerList.push_back(playerOne);
                cout << "Player 1 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerTwo);
                cout << "Player 2 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerThree);
                cout << "Player 3 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerFour);
                cout << "Player 4 is created with empty card deck and empty territory" << "\n";
                checkinput = false;
                NumberOfPlayersGlobal=4;
                break;}
            case 5:
            {cout << "you choose 5 players" << "\n";
                std::vector<Territory*> territoryPlayerOne;
                std::vector<Territory*> territoryPlayerTwo;
                std::vector<Territory*> territoryPlayerThree;
                std::vector<Territory*> territoryPlayerFour;
                std::vector<Territory*> territoryPlayerFive;
                PlayerStrategies* Playerstrategies1= new PlayerStrategies();
                PlayerStrategies* Playerstrategies2= new PlayerStrategies();
                PlayerStrategies* Playerstrategies3= new PlayerStrategies();
                PlayerStrategies* Playerstrategies4= new PlayerStrategies();
                PlayerStrategies* Playerstrategies5= new PlayerStrategies();
                Player* playerOne = new Player("Player1",territoryPlayerOne,Playerstrategies1);
                Player* playerTwo = new Player("Player2",territoryPlayerTwo,Playerstrategies2);
                Player* playerThree = new Player("Player3",territoryPlayerThree,Playerstrategies3);
                Player* playerFour = new Player("Player4",territoryPlayerFour,Playerstrategies4);
                Player* playerFive = new Player("Player5",territoryPlayerFive,Playerstrategies5);
                PlayerList.push_back(playerOne);
                cout << "Player 1 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerTwo);
                cout << "Player 2 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerThree);
                cout << "Player 3 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerFour);
                cout << "Player 4 is created with empty card deck and empty territory" << "\n";
                PlayerList.push_back(playerFive);
                cout << "Player 5 is created with empty card deck and empty territory" << "\n";
                checkinput = false;
                NumberOfPlayersGlobal=5;
                break;}
            default: {
                cout << "Not a valid input " << "\n";
                cout << "ReEnter your input between 2 to 5" << "\n";
                cin >> NumberOfPlayers;
                checkinput = true;
            }
        }
    }

}

void StartUp::StartUpPhase() {
    HelperFunction helper;
    cout << "The number of continents is :  " << helper.ReturnNumberOfContinents() << endl;
    cout << "The number of contries is :  " << helper.ReturnNumberOfContries() << endl;
    //Create continents list
    for (int i = 0; i < helper.ReturnNumberOfContinents(); i++) {
        Continent *continentbuffer = new Continent();
        continentbuffer->ContinentNum = i;
        continentbuffer->Continetname = ContinentNameFromMap[i];
        continentbuffer->BonusValue = ContinentBonusFromMap[i];
        ContinentList.push_back(continentbuffer);
//        cout << "Continent value inside ContinentList" << endl;
//        cout << "Continent Name is : " << ContinentList[i]->GetContinentName() << endl;
//        cout << "Continent Number is : " << ContinentList[i]->ContinentNum << endl;
//        cout << "Continent Bonus is : " << ContinentList[i]->BonusValue << endl;
//        delete continentbuffer;
    }

    //create territory list
    for (int i = 0; i < helper.ReturnNumberOfContries(); i++) {
        Territory *territorybuffer = new Territory();
        territorybuffer->TerritoryNumber = i;
        territorybuffer->TerritoryName = ContriesNameFromMap[i];
        territorybuffer->NumberOfTroops = 0;
        territorybuffer->OwnerName = "None";
        territorybuffer->ContinentName = "None";
        territorybuffer->ContinentNum = 0;
        TerritoryList.push_back(territorybuffer);
//        cout << "Continent value inside TerritoryList" << endl;
//        cout << "Territory Number is : " << TerritoryList[i]->TerritoryNumber << endl;
//        cout << "Territory Name is : " << TerritoryList[i]->TerritoryName << endl;
//        cout << "Territory Troops is : " << TerritoryList[i]->NumberOfTroops << endl;
//        cout << "Territory Owner name is : " << TerritoryList[i]->OwnerName << endl;
//        cout << "Territory Continent name is : " << TerritoryList[i]->ContinentName << endl;
//        cout << "Territory Continent number is : " << TerritoryList[i]->ContinentNum << endl;
    }


//    create Continents Territory Connection
    for (int i = 0; i < helper.ReturnNumberOfContries(); i++) {
        for (int j = 0; j < helper.ReturnNumberOfContinents(); j++) {
            if (ContriesNumberBelongsToContinents[i] - 1 == j) {
                ContinentList[j]->territories.push_back(TerritoryList[i]);
            }
        }
    }
    //check ContinentList for brasil case
//    cout << ContinentList[0]->territories.size() << endl;
//    cout << ContinentList[1]->territories.size() << endl;
//    cout << ContinentList[2]->territories.size() << endl;
//    cout << ContinentList[3]->territories.size() << endl;
//    cout << ContinentList[4]->territories.size() << endl;
    //check Continents Territory Connection
//    for (int i = 0; i < ContinentList.size(); i++) {
//        for (int j = 0; j < ContinentList[i]->territories.size(); j++) {
//            cout << "Continent " << i + 1 << " has " << ContinentList[i]->territories[j]->TerritoryName << endl;
//        }
//    }

    int AssignTerritoryBuffer[HelperFunction().ReturnNumberOfContries()];
    switch (NumberOfPlayersGlobal) {
        case 2: {
            srand(time(NULL));
            for (int i = 0; i < HelperFunction().ReturnNumberOfContries(); i++) {
                AssignTerritoryBuffer[i] = rand() % 2;
            }
            for (int i = 0; i < HelperFunction().ReturnNumberOfContries(); i++) {
                if (AssignTerritoryBuffer[i] == 0) {
                    PlayerList[0]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player1",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                                                                         ));
                }
                if (AssignTerritoryBuffer[i] == 1) {
                    PlayerList[1]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player2",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
            }
            PlayerList[0]->reinforcementPool = 40;
            cout << "Player 1 has initialized with 40 armies" << "\n";
            PlayerList[1]->reinforcementPool = 40;
            cout << "Player 2 has initialized with 40 armies" << "\n";
            //test
            for (int i = 0; i < PlayerList[0]->territoryList.size(); i++) {
                cout << "Player1 has : "<< PlayerList[0]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[1]->territoryList.size(); i++) {
                cout << "Player2 has : "<< PlayerList[1]->territoryList[i]->TerritoryName<<endl;
            }
            break;
        }
        case 3:{
            srand(time(NULL));
            for(int i = 0; i<HelperFunction().ReturnNumberOfContries();i++){
                AssignTerritoryBuffer[i]=rand() % 3 ;
            }
            for (int i = 0; i < HelperFunction().ReturnNumberOfContries(); i++) {
                if (AssignTerritoryBuffer[i] == 0) {
                    PlayerList[0]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player1",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));
                }
                if (AssignTerritoryBuffer[i] == 1) {
                    PlayerList[1]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player2",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 2) {
                    PlayerList[2]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player3",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
            }
            PlayerList[0]->reinforcementPool = 35;
            cout << "Player 1 has initialized with 35 armies" << "\n";
            PlayerList[1]->reinforcementPool = 35;
            cout << "Player 2 has initialized with 35 armies" << "\n";
            PlayerList[2]->reinforcementPool = 35;
            cout << "Player 3 has initialized with 35 armies" << "\n";

            //test
            for (int i = 0; i < PlayerList[0]->territoryList.size(); i++) {
                cout << "Player1 has : "<< PlayerList[0]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[1]->territoryList.size(); i++) {
                cout << "Player2 has : "<< PlayerList[1]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[2]->territoryList.size(); i++) {
                cout << "Player3 has : "<< PlayerList[2]->territoryList[i]->TerritoryName<<endl;
            }
            break;
        }
        case 4: {
            srand(time(NULL));
            for(int i = 0; i<HelperFunction().ReturnNumberOfContries();i++){
                AssignTerritoryBuffer[i]=rand() % 4 ;
            }
            for (int i = 0; i < HelperFunction().ReturnNumberOfContries(); i++) {
                if (AssignTerritoryBuffer[i] == 0) {
                    PlayerList[0]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player1",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));
                }
                if (AssignTerritoryBuffer[i] == 1) {
                    PlayerList[1]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player2",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 2) {
                    PlayerList[2]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player3",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 3) {
                    PlayerList[3]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player4",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
            }
            PlayerList[0]->reinforcementPool = 30;
            cout << "Player 1 has initialized with 30 armies" << "\n";
            PlayerList[1]->reinforcementPool = 30;
            cout << "Player 2 has initialized with 30 armies" << "\n";
            PlayerList[2]->reinforcementPool = 30;
            cout << "Player 3 has initialized with 30 armies" << "\n";
            PlayerList[3]->reinforcementPool = 30;
            cout << "Player 4 has initialized with 30 armies" << "\n";

            //test
            for (int i = 0; i < PlayerList[0]->territoryList.size(); i++) {
                cout << "Player1 has : "<< PlayerList[0]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[1]->territoryList.size(); i++) {
                cout << "Player2 has : "<< PlayerList[1]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[2]->territoryList.size(); i++) {
                cout << "Player3 has : "<< PlayerList[2]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[3]->territoryList.size(); i++) {
                cout << "Player4 has : "<< PlayerList[3]->territoryList[i]->TerritoryName<<endl;
            }
            break;
        }
        case 5: {
            srand(time(NULL));
            for(int i = 0; i<HelperFunction().ReturnNumberOfContries();i++){
                AssignTerritoryBuffer[i]=rand() % 5 ;
            }
            for (int i = 0; i < HelperFunction().ReturnNumberOfContries(); i++) {
                if (AssignTerritoryBuffer[i] == 0) {
                    PlayerList[0]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player1",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));
                }
                if (AssignTerritoryBuffer[i] == 1) {
                    PlayerList[1]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player2",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 2) {
                    PlayerList[2]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player3",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 3) {
                    PlayerList[3]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player4",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
                if (AssignTerritoryBuffer[i] == 4) {
                    PlayerList[4]->territoryList.push_back(new Territory(TerritoryList[i]->TerritoryNumber,
                                                                         TerritoryList[i]->TerritoryName,
                                                                         0,
                                                                         "Player5",
                                                                         TerritoryList[i]->ContinentNum,
                                                                         TerritoryList[i]->GetContinentName()
                    ));

                }
            }
            PlayerList[0]->reinforcementPool = 25;
            cout << "Player 1 has initialized with 25 armies" << "\n";
            PlayerList[1]->reinforcementPool = 25;
            cout << "Player 2 has initialized with 25 armies" << "\n";
            PlayerList[2]->reinforcementPool = 25;
            cout << "Player 3 has initialized with 25 armies" << "\n";
            PlayerList[3]->reinforcementPool = 25;
            cout << "Player 4 has initialized with 25 armies" << "\n";
            PlayerList[4]->reinforcementPool = 25;
            cout << "Player 5 has initialized with 25 armies" << "\n";
            //test
            for (int i = 0; i < PlayerList[0]->territoryList.size(); i++) {
                cout << "Player1 has : "<< PlayerList[0]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[1]->territoryList.size(); i++) {
                cout << "Player2 has : "<< PlayerList[1]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[2]->territoryList.size(); i++) {
                cout << "Player3 has : "<< PlayerList[2]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[3]->territoryList.size(); i++) {
                cout << "Player4 has : "<< PlayerList[3]->territoryList[i]->TerritoryName<<endl;
            }
            for (int i = 0; i < PlayerList[4]->territoryList.size(); i++) {
                cout << "Player5 has : "<< PlayerList[4]->territoryList[i]->TerritoryName<<endl;
            }
            break;
        }
    }




            cout << "end of start up phase" << endl;
}

void GameLoop::ReinforcementPhase(){
    HelperFunction helper;
    string playerName = "";
    string buff;
    string buffstrtegy;
    bool ChangeStretegy = false;
    cout <<"Start of ReinforcementPhase"<<endl;
    cout <<"Do you want to change each player's strategy?(yes/no)"<<endl;
    cin >> buff;
    if(buff=="yes"){ChangeStretegy=true;}
    if(buff=="no"){ChangeStretegy=false;}


    cout << "set your stategy for each player now"<<endl;
    //status report
    for(int i =0;i < PlayerList.size();i++){
        cout << "The type of "<<PlayerList[i]->getPlayerName()<<" is " << PlayerList[i]->Playerstrategies->PlayerStatus<<endl;
    }

    if(ChangeStretegy){
        for(int i =0;i < PlayerList.size();i++){
            cout <<PlayerList[i]->getPlayerName()<<endl;
            cout << "you want to change this player strategy to? :"<<endl;
            cout << "options:human aggressive benevolent neutral"<<endl;
            cin>> buffstrtegy;
            if(buffstrtegy =="human"){PlayerList[i]->setStrategies("human");}
            if(buffstrtegy =="aggressive"){PlayerList[i]->setStrategies("aggressive");}
            if(buffstrtegy =="benevolent"){PlayerList[i]->setStrategies("benevolent");}
            if(buffstrtegy =="neutral"){PlayerList[i]->setStrategies("neutral");}
        }
    }


    for(int i =0;i < PlayerList.size();i++){
        cout << "The type of "<<PlayerList[i]->getPlayerName()<<" is " << PlayerList[i]->Playerstrategies->PlayerStatus<<endl;
    }

    cout <<"Each player gets armies first"<<endl;
    for(int i = 0 ; i< NumberOfPlayersGlobal;i++){
        PlayerList[i]->reinforcementPool+=(int)PlayerList[i]->territoryList.size()/3;
        cout <<"now player " << i<<" has "<<PlayerList[i]->reinforcementPool<<" armies in their reinforcementpool"<<endl;

    }

//    cout <<"Each player gets bonus depends on their owned territory"<<endl;
//    for(int i = 0 ; i<= helper.ReturnNumberOfContinents()-1;i++){
//        int buffer = 0;
//        vector<Territory> Tbuff =  ContinentList[i].ReturnTerritory();
//        for(int j = 0;j<helper.ReturnNumberOfContinents();j++){
//            if(Tbuff[j].GetPlayerName() == Tbuff[j].GetPlayerName()){
//                buffer++;
//                if(buffer>helper.ReturnNumberOfContinents()+2){
//                    PlayerList[i].reinforcementPool += ContinentBonusFromMap[i];
//                    cout << "Player " << i << " gets bonus of " << ContinentBonusFromMap[i] << endl;
//                }
//                else
//                {
//                    cout<<"No bonus for continents "<<ContinentList[i].GetContinentName()<<endl;
//                }
//            }
//        }
//    }
    cout<<"End of reinforcement phase "<<endl;
};
void GameLoop::IssueOrderPhase(){
    Deck deck = Deck();
    int fromTerritory;
    int toTerritory;
    int territoryToDeploy;
    int numOfArmies;
    int issueAdvance;
    int choose;
    int playername;
    bool stopbuffer =true;
    cout<<"Begin IssueOrder phase "<<endl;
    for(int i = 0;i < PlayerList.size();i++){
        if (PlayerList[i]->Playerstrategies->PlayerStatus == "human"){
            cout << PlayerList[i]->getPlayerName()<<" is a human player, begin issue orders"<<endl;
            cout<<"Begin issue deploy order"<<endl;
            while (PlayerList[i]->getReinforcementPool()>0) {
                cout << PlayerList[i]->getPlayerName() << " Territory list: ";
                for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                     cout << PlayerList[i]->territoryList[j]->TerritoryNumber << "  ";
                }
                cout << endl;
                cout << PlayerList[i]->getPlayerName() << " Army list: ";
                for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                       cout  << PlayerList[i]->territoryList[j]->NumberOfTroops << "  ";
                }
                cout << endl;
                cout << "You have: " << PlayerList[i]->reinforcementPool << " in your reinforcementPool" << endl;
                cout << "enter territory number"<<endl;
                cin >> territoryToDeploy;
                cout << "enter number of armies"<<endl;
                cin >> numOfArmies;
                PlayerList[i]->setReinforcementPool(PlayerList[i]->getReinforcementPool()-numOfArmies);
                Deploy* deploy;
                for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                    if(PlayerList[i]->territoryList[k]->TerritoryNumber==territoryToDeploy ){
                        deploy= new Deploy(PlayerList[i],PlayerList[i]->territoryList[k],numOfArmies);
                    }
                }
                cout<<"successful add to player orderlist"<<endl;
                PlayerList[i]->player_ordersList.push_back(deploy);
//                PlayerList[i]->player_ordersList[0]->execute();
            }
            cout<<"deploy end"<<endl;
            cout<<"Begin issue advance order"<<endl;
            while(stopbuffer){
                cout<<PlayerList[i]->getPlayerName()<<", do you want to issue advance order? if yes(1)/if no(0)"<<endl;
                cin>>issueAdvance;
                if (issueAdvance ==0){break;}
                if (issueAdvance ==1){
            cout<<"choose defend or attack. defend(0)/attack(1)"<<endl;
            cin>>choose;
            if(choose==0){
                cout<< PlayerList[i]->getPlayerName()<<endl;
                cout << "from territory: "<<endl;
                cin >> fromTerritory;
                cout << "to territory: "<<endl;
                cin >> toTerritory;
                cout << "numofarmies: "<<endl;
                cin >> numOfArmies;
                int fromT;
                int toT;
                for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                    if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                        fromT = k;
                    }
                    if(PlayerList[i]->territoryList[k]->TerritoryNumber==toTerritory ){
                        toT = k;
                    }
                }
                if(PlayerList[i]->territoryList[fromT]->GetNumOfTroops()-numOfArmies>=0){
                    //todo
                    Advance* advanceDefend = new Advance(PlayerList[i],PlayerList[i]->territoryList[fromT],PlayerList[i]->territoryList[toT],numOfArmies);
                    cout<<"successful add to player orderlist"<<endl;
                    PlayerList[i]->player_ordersList.push_back(advanceDefend);
                }
                else{
                    cout<<"numOfArmies is over the Territory's NumOfTroops"<<endl;}
            }
            else if(choose==1){
                cout<< PlayerList[i]->getPlayerName()<<endl;
                cout << "from territory: "<<endl;
                cin >> fromTerritory;
                cout << "to territory: "<<endl;
                cin >> toTerritory;
                cout << "numofarmies: "<<endl;
                cin >> numOfArmies;
                //判断是否isneighbor
                int fromT;
                int toT;
                int toP;
                for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                    if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                        fromT = k;
                    }
//                    if(TerritoryList[k]->TerritoryNumber==toTerritory ){
//                        toT = k;
//                    }
                }
                for(int k=0;k<PlayerList.size();k++){
                    for(int j=0;j<PlayerList[k]->territoryList.size();j++){
                        if(PlayerList[k]->territoryList[j]->TerritoryNumber==toTerritory){
                            toT=j;
                            toP=k;
                            break;
                        }
                    }
                }

                if (true)
                {
                    //todo
                    cout<<"they are neighbors, successful add to player orderlist"<<endl;
                    Advance* advanceAttack = new Advance(PlayerList[i],PlayerList[i]->territoryList[fromT],PlayerList[toP]->territoryList[toT],numOfArmies);
                    PlayerList[i]->player_ordersList.push_back(advanceAttack);
                }
                else{
                    cout<<"they are not neighbors"<<endl;
                }
            }

            cout<<"do you want to continue to issue advance order? if yes(1)/if no(0)"<<endl;
            cin>>issueAdvance;
            if(issueAdvance == 0){break;}
             }
            }
            cout<<"End of advance order"<<endl;
        cout<<"Begin use card to issue order"<<endl;
        cout<<"draw one card in Game Deck"<<endl;
        Hand hand=Hand();
        Card card=deck.draw(hand);
        cout<<"0=bomb, 1=reinforcement, 2=blockade, 3=airlift, 4=diplomacy"<<endl;
        cout<<"this card is "<<card<<endl;
        cout<<"do you want to use this card? yes(1)/no(0)"<<endl;
        cin>>choose;
        if(choose==1){
            switch (*(card.getCardType())) {
                case bomb:{
                    cout<<"bomb order: enter # of territory in your AttackList"<<endl;
                    cin>>toTerritory;
                    card.play(hand,deck);
                    int toT;
                    for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                        if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                            toT = k;
                        }
                    }
                    Bomb* bomb=new Bomb(PlayerList[i],PlayerList[i]->territoryList[toT]);
                    cout<<"successful add to player orderlist"<<endl;
                    PlayerList[i]->player_ordersList.push_back(bomb);
                    break;
                }
                case blockade:{
                    cout<<"blockade order: enter # of territory in your DefendList"<<endl;
                    cin>>toTerritory;
                    card.play(hand,deck);
                    int toT;
                    for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                        if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                            toT = k;
                        }
                    }
                    Blockade* blockade=new Blockade(PlayerList[i],PlayerList[i]->territoryList[toT]);
                    cout<<"successful add to player orderlist"<<endl;
                    PlayerList[i]->player_ordersList.push_back(blockade);
                    break;
                }
                case airlift:{
                    cout<<"airlift order: enter # of territory in your playerTerritory,and # of toerritory in your AttackList, and # armies"<<endl;
                    cin>>fromTerritory;
                    cin>>toTerritory;
                    cin>>numOfArmies;
                    card.play(hand,deck);
                    int fromT;
                    int toT;
                    for(int k=0;k<PlayerList[i]->territoryList.size();k++){
                        if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                            fromT = k;
                        }
                        if(PlayerList[i]->territoryList[k]->TerritoryNumber==fromTerritory ){
                            toT = k;
                        }
                    }
                    Airlift* airlift=new Airlift(PlayerList[i],PlayerList[i]->territoryList[fromT],PlayerList[i]->territoryList[toT],numOfArmies);
                    cout<<"successful add to player orderlist"<<endl;
                    PlayerList[i]->player_ordersList.push_back(airlift);
                    break;

                }
                case diplomacy:{
                    cout<<"negotiate order: enter an index in PlayerList"<<endl;
                    cin>>playername;
                    card.play(hand,deck);
                    Negotiate* negotiate=new Negotiate(PlayerList[i],PlayerList[playername]);
                    cout<<"successful add to player orderlist"<<endl;
                    PlayerList[i]->player_ordersList.push_back(negotiate);
                    break;
                }
            }
        }


        }
        if (PlayerList[i]->Playerstrategies->PlayerStatus == "aggressive"){
            cout << PlayerList[i]->getPlayerName()<<" is a aggressive player, orders are put in orderlist now"<<endl;

            cout << PlayerList[i]->getPlayerName() << " Territory list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout << PlayerList[i]->territoryList[j]->TerritoryNumber << "  ";
            }
            cout << endl;
            cout << PlayerList[i]->getPlayerName() << " Army list: ";
            int count = 0;
            int maxnumberoftroops=0;
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                count++;
                PlayerList[i]->territoryList[j]->NumberOfTroops+=count;
                if(PlayerList[i]->territoryList[j]->NumberOfTroops>maxnumberoftroops){
                    maxnumberoftroops=PlayerList[i]->territoryList[j]->NumberOfTroops;
                }
                cout  << PlayerList[i]->territoryList[j]->NumberOfTroops << "  ";
            }
            cout << endl;
            Deploy *deploy2;
            Advance* advance2;
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                if(PlayerList[i]->territoryList[j]->NumberOfTroops == maxnumberoftroops){
                    cout << "the strongest territory is "<<PlayerList[i]->territoryList[j]->TerritoryName<<endl;
                    cout<< "it has "<<maxnumberoftroops<<" troops ";
                    cout << "now we deploy all the troops to this territory "<<endl;
                    if(PlayerList[i]->territoryList[j]->NumberOfTroops>0) {
                        deploy2 = new Deploy(PlayerList[i], PlayerList[i]->territoryList[j],PlayerList[i]->reinforcementPool);
                    }
                }
            }
            cout << "now we put deploy into orders list "<<endl;
            PlayerList[i]->player_ordersList.push_back(deploy2);

//            deploy2->execute();
            cout << PlayerList[i]->getPlayerName() << " Territory list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout << PlayerList[i]->territoryList[j]->TerritoryNumber << "  ";
            }
            cout << endl;
            cout << PlayerList[i]->getPlayerName() << " Army list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout  << PlayerList[i]->territoryList[j]->NumberOfTroops << "  ";
            }
            cout << endl;
            for(int q = 0;q<PlayerList[i]->territoryList.size();q++){
                for(int p = 0;p<TerritoryList.size();p++){
                    if(ConnectionBufferFromMap[q][p]==1 && q!=p){
                        //todo
                        Advance* advanceAttack = new Advance(PlayerList[i],PlayerList[i]->territoryList[q],TerritoryList[p],PlayerList[i]->territoryList[q]->NumberOfTroops);
                        PlayerList[i]->player_ordersList.push_back(advanceAttack);
                        break;
                    }
                }
            }
            cout << "now we put attack into orders list "<<endl;
            cout << endl;
        }







        if (PlayerList[i]->Playerstrategies->PlayerStatus == "benevolent"){
            cout << PlayerList[i]->getPlayerName()<<" is a benevolent player, orders are put in orderlist now"<<endl;
            cout << PlayerList[i]->getPlayerName() << " Territory list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout << PlayerList[i]->territoryList[j]->TerritoryNumber << "  ";
            }
            cout << endl;
            cout << PlayerList[i]->getPlayerName() << " Army list: ";
            int count = 0;
            int maxnumberoftroops=0;
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                count++;
                PlayerList[i]->territoryList[j]->NumberOfTroops+=count;
                if(PlayerList[i]->territoryList[j]->NumberOfTroops>maxnumberoftroops){
                    maxnumberoftroops=PlayerList[i]->territoryList[j]->NumberOfTroops;
                }
                cout  << PlayerList[i]->territoryList[j]->NumberOfTroops << "  ";
            }
            cout << endl;
            Deploy *deploy2;
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                if(PlayerList[i]->territoryList[j]->NumberOfTroops == maxnumberoftroops){
                    cout << "the weakest territory is "<<PlayerList[i]->territoryList[j]->TerritoryName<<endl;
                    cout<< "it has "<<maxnumberoftroops<<" troops ";
                    cout << "now we deploy all the troops to this territory "<<endl;
                    if(PlayerList[i]->territoryList[j]->NumberOfTroops>0) {
                        deploy2 = new Deploy(PlayerList[i], PlayerList[i]->territoryList[j],PlayerList[i]->reinforcementPool);
                    }
                }
            }
            cout << "now we put deploy into orders list "<<endl;
            PlayerList[i]->player_ordersList.push_back(deploy2);

//            deploy2->execute();
            cout << PlayerList[i]->getPlayerName() << " Territory list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout << PlayerList[i]->territoryList[j]->TerritoryNumber << "  ";
            }
            cout << endl;
            cout << PlayerList[i]->getPlayerName() << " Army list: ";
            for (int j = 0; j < PlayerList[i]->territoryList.size(); j++) {
                cout  << PlayerList[i]->territoryList[j]->NumberOfTroops << "  ";
            }
            cout << endl;
            cout << "now we put attack into orders list "<<endl;
            cout << endl;
        }
        if (PlayerList[i]->Playerstrategies->PlayerStatus == "neutral"){
            cout << PlayerList[i]->getPlayerName()<<" is a neutral player, no orders are put in orderlist"<<endl;
        }
    }










//    int fromTerritory;
//    int toTerritory;
//    int territoryToDeploy;
//    int numOfArmies;
//    int issueAdvance;
//    int choose;
//    int playername;

//    for(int i =0;i<PlayerList.size();i++){
//        vector<Territory*> ToAttack;
//        for(int j=0;j<PlayerList.size();j++){
//            //没有判断是否isneighbor
//            if(PlayerList[j]->getPlayerName()!=PlayerList[i]->getPlayerName()){
//                for(int k=0; k<PlayerList[j]->getTerritoryList().size();k++){
//                    ToAttack.push_back(PlayerList[j]->getTerritoryList()[k]);
//                }
//            }
//        }
//        cout<<"Begin issue deploy order"<<endl;
//        while (PlayerList[i]->getReinforcementPool()>0){
//            cout << PlayerList[i]->getPlayerName() << ", issue depoly order: enter # of territory in Defendlist and # of armies "<< endl;
//            cin>>territoryToDeploy;
//            cin>>numOfArmies;
//            if((PlayerList[i]->getReinforcementPool() - numOfArmies)>=0){
//                PlayerList[i]->setReinforcementPool(PlayerList[i]->getReinforcementPool()-numOfArmies);
//                Deploy* deploy= new Deploy(PlayerList[i],PlayerList[i]->toDefend()[territoryToDeploy],numOfArmies);
//                cout<<"successful add to player orderlist"<<endl;
//                PlayerList[i]->getOrdersList().push_back(deploy);
//            }
//        }
//        cout<<"Begin issue advance order"<<endl;
//        cout<<PlayerList[i]->getPlayerName()<<", do you want to issue advance order? if yes(1)/if no(0)"<<endl;
//        cin>>issueAdvance;
//        if (issueAdvance ==1){
//            cout<<"choose defend or attack. defend(0)/attack(1)"<<endl;
//            cin>>choose;
//            if(choose==0){
//                cout<< PlayerList[i]->getPlayerName() << ", issue advance order: enter from which # of territory in playerTerritory, to which # of territory in Defendlist and # of armies "<< endl;
//                cin >> fromTerritory;
//                cin >> toTerritory;
//                cin >> numOfArmies;
//                if(PlayerList[i]->toDefend()[fromTerritory]->GetNumOfTroops()-numOfArmies>=0){
//                    Advance* advanceDefend = new Advance(PlayerList[i],PlayerList[i]->toDefend()[fromTerritory],PlayerList[i]->toDefend()[toTerritory],numOfArmies);
//                    cout<<"successful add to player orderlist"<<endl;
//                    PlayerList[i]->getOrdersList().push_back(advanceDefend);
//                }
//                else{
//                    cout<<"numOfArmies is over the Territory's NumOfTroops"<<endl;}
//            }
//            else if(choose==1){
//                cout<< PlayerList[i]->getPlayerName() << ", issue advance order: enter from which # of territory in playerTerritory, to which # of territory in Attacklist and # of armies "<< endl;
//                cin >> fromTerritory;
//                cin >> toTerritory;
//                cin >> numOfArmies;
//                //判断是否isneighbor
//                if (true)
//                {
//                    cout<<"they are neighbors, successful add to player orderlist"<<endl;
//                    Advance* advanceAttack = new Advance(PlayerList[i],PlayerList[i]->getTerritoryList()[fromTerritory],ToAttack[toTerritory],numOfArmies);
//                    PlayerList[i]->getOrdersList().push_back(advanceAttack);
//                }
//                else{
//                    cout<<"they are not neighbors"<<endl;
//                }
//            }
//
//            cout<<"do you want to continue to issue advance order? if yes(1)/if no(0)"<<endl;
//            cin>>issueAdvance;
//        }
//        cout<<"Begin use card to issue order"<<endl;
//        cout<<"draw one card in Game Deck"<<endl;
//        //没有分配player Hand，只能这里先创建一个；
//        Hand hand=Hand();
//        Card card=deck.draw(hand);
//        cout<<"0=bomb, 1=reinforcement, 2=blockade, 3=airlift, 4=diplomacy"<<endl;
//        cout<<"this card is "<<card<<endl;
//        cout<<"do you want to use this card? yes(1)/no(0)"<<endl;
//        cin>>choose;
//        if(choose==1){
//
//            switch (*(card.getCardType())) {
//                case bomb:{
//                    cout<<"bomb order: enter # of territory in your AttackList"<<endl;
//                    cin>>toTerritory;
//                    card.play(hand,deck);
//                    Bomb* bomb=new Bomb(PlayerList[i],ToAttack[toTerritory]);
//                    cout<<"successful add to player orderlist"<<endl;
//                    PlayerList[i]->getOrdersList().push_back(bomb);
//                    break;
//                }
//                case blockade:{
//                    cout<<"blockade order: enter # of territory in your DefendList"<<endl;
//                    cin>>toTerritory;
//                    card.play(hand,deck);
//                    Blockade* blockade=new Blockade(PlayerList[i],PlayerList[i]->toDefend()[toTerritory]);
//                    cout<<"successful add to player orderlist"<<endl;
//                    PlayerList[i]->getOrdersList().push_back(blockade);
//                    break;
//                }
//                case airlift:{
//                    cout<<"airlift order: enter # of territory in your playerTerritory,and # of toerritory in your AttackList, and # armies"<<endl;
//                    cin>>fromTerritory;
//                    cin>>toTerritory;
//                    cin>>numOfArmies;
//                    card.play(hand,deck);
//                    Airlift* airlift=new Airlift(PlayerList[i],PlayerList[i]->getTerritoryList()[fromTerritory],ToAttack[toTerritory],numOfArmies);
//                    cout<<"successful add to player orderlist"<<endl;
//                    PlayerList[i]->getOrdersList().push_back(airlift);
//                    break;
//
//                }
//                case diplomacy:{
//                    cout<<"negotiate order: enter an index in PlayerList"<<endl;
//                    cin>>playername;
//                    card.play(hand,deck);
//                    Negotiate* negotiate=new Negotiate(PlayerList[i],PlayerList[playername]);
//                    cout<<"successful add to player orderlist"<<endl;
//                    PlayerList[i]->getOrdersList().push_back(negotiate);
//                    break;
//
//                }
//
//            }
//
//        }
//
//
//
//    }



}
void GameLoop::OrdersExecutionPhase(){
    //todo
    cout <<"begin orders execution"<<endl;
    for(int i =0;i<PlayerList.size();i++) {
        for (int j = 0; j < PlayerList[i]->player_ordersList.size(); j++) {
//            cout << PlayerList[i]->player_ordersList[0]->getType()<<endl;
//            cout<<PlayerList[i]->player_ordersList[1]->getType()<<endl;
//            cout<<PlayerList[i]->player_ordersList[2]->getType()<<endl;
            cout<< PlayerList[i]->getPlayerName()<<" has "<<PlayerList[i]->player_ordersList.size() << " orders ";

            PlayerList[i]->player_ordersList[j]->execute();
            cout<<"order executed"<<endl;
        }

    }
    for (int i=0;i<PlayerList.size();i++){
        for(int j = 0; j < PlayerList[i]->player_ordersList.size(); j++){
            delete PlayerList[i]->player_ordersList[j];
            PlayerList[i]->player_ordersList.erase(PlayerList[i]->player_ordersList.begin()+j);
            cout<<"order erased"<<endl;
        }
    }
    cout <<"end orders execution"<<endl;

//
//    //finding the max number of orders from one ordersList
//    int maxOrderNum = 0;
//    for (int i = 0; i < PlayerList.size(); i++) {
//        if (maxOrderNum < PlayerList[i]->getOrdersList().size()) {
//            maxOrderNum = PlayerList[i]->getOrdersList().size();
//        }
//    }
//
//    cout << "\n>>>>> Priority orders <<<<< \n    maximum of order -> " << maxOrderNum << "\n";
//    //find and execute every player's deploy
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Deploy of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Deploy") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//    //find and execute player's airlift
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Airlift of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Airlift") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//                break;
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//    //find and execute player's blockade
//    for (int i = 0; i < PlayerList.size(); i++) {
//        cout << "Blockade of " << PlayerList[i]->getPlayerName() << ": \n";
//        for (int j = 0; j < PlayerList[i]->getOrdersList().size(); j++) {
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Blockade") {
//                cout << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//                break;
//            } else { cout << "\tOrder #" << j << " pass" << endl; }
//        }
//    }
//
//    cout << ">>>>> Non-priority orders <<<<< \n";
//    //execute other orders in round robin fashion
//    for (int i = 0; i < PlayerList.size(); i++) {
//        for (int j = 0; j < maxOrderNum; j++) {
//
//            if (PlayerList[i]->getOrdersList()[j]->getType() == "Bomb" ||
//                PlayerList[i]->getOrdersList()[j]->getType() == "Advance" ||
//                PlayerList[i]->getOrdersList()[j]->getType() == "Negotiate") {
//                cout << PlayerList[i]->getPlayerName() << "\tOrder #" << j << " >>> ";
//                PlayerList[i]->getOrdersList()[j]->execute();
//            } else { cout << PlayerList[i]->getPlayerName() << "\tOrder #" << j << " pass" << endl; }
//
//        }
//    }
//
//    //clear each player's ordersList for this round

//    for (int i=0;i<PlayerList.size();i++){
//        for(int j = 0; j < PlayerList[i]->player_ordersList.size(); j++){
//            //avoid memory leak!!!!!//
//            delete PlayerList[i]->player_ordersList[j];
//            PlayerList[i]->player_ordersList.erase(PlayerList[i]->player_ordersList.begin()+j);
//            cout<<"order erased"<<endl;
//        }
//    }
//
////        cout << "P1 Order List should be empty: ";
////        for (int i = 0; i < PlayerList[0]->getOrdersList().size(); i++) {
////            cout << PlayerList[0]->getOrdersList()[i]->getType() << ", ";
////        }
////        cout << endl;
////        cout << "P2 Order List should be empty: ";
////        for (int i = 0; i < PlayerList[1]->getOrdersList().size(); i++) {
////            cout << PlayerList[1]->getOrdersList()[i]->getType() << ", ";
////        }
//    cout << endl;
};
void GameLoop::WinningConditionValidation(){
    cout << "\n---------- Winning Check -----------" << endl;

    Player* winner;
    //win condition
    for (int i = 0; i < PlayerList.size(); i++) { //for each player
        int terrCount = 0;
        for (int j = 0; j < TerritoryList.size(); j++) { // for each territory
            if (PlayerList[i]->getPlayerName() != TerritoryList[j]->GetOwnererName()) {
                cout << PlayerList[i]->getPlayerName() << " is not the winner," << " he has " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
                break;
            } else { terrCount++;}
            if (terrCount == TerritoryList.size()) {
                winner = PlayerList[i];
                cout << winner->getPlayerName()+ " is the winner," << " he has " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
            }
        }
    }
    //lose condition
    for (int i = 0; i < PlayerList.size(); i++) { //for each player
        int terrCount = 0;
        for (int j = 0; j < TerritoryList.size(); j++) { // for each territory
            if (PlayerList[i]->getPlayerName() == TerritoryList[j]->GetOwnererName()) {
                cout << PlayerList[i]->getPlayerName() << " has not been defeated yet," << " he has lost " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
                break;
            } else { terrCount++;}
            if (terrCount == TerritoryList.size()) {
                cout << PlayerList[i]->getPlayerName()+ " has been defeated," << " he does not have " << terrCount << " out of " << TerritoryList.size() << " territory(s).\n";
            }
        }
    }
};






int main() {
    GameStart gamestart;
    gamestart.ChooseMap();
    gamestart.ChooseNumberOfPlayers();
    StartUp gameStartUp;
    gameStartUp.StartUpPhase();
    GameLoop gameloop;
    while(true) {
        gameloop.ReinforcementPhase();
        gameloop.IssueOrderPhase();
        gameloop.OrdersExecutionPhase();
    }


//    cout<<"------------Test Card------------"<<endl;
//    Deck deck=Deck(2);
//    Hand hand=Hand();
//    Card card=deck.draw(hand);
//    cout<<hand<<endl;
//    cout<<deck<<endl;
//    cout<<card<<endl;
//    card.play(hand,deck);
//    cout<<hand<<endl;
//    cout<<deck<<endl;
//    card.~Card();
//    hand.~Hand();
//    deck.~Deck();

//__________________test order_________________________//
// Create some players and territories to do the tests
//cout<<"__________________test order_________________________"<<endl;
//    Player* player1;
//    Player* player2;
//
//    Territory* USA =new Territory(1,"USA", 10, "player1",0,"NA");
//    Territory* Canada =new Territory(2,"Canada", 10, "player2",0,"NA");
//    Territory* Mexico =new Territory(3,"Mexico", 10, "player1",0,"NA");
//    Territory* Cuba =new Territory(4,"Cuba", 10, "player2",0,"NA");
//    vector<Territory*> list;
//    list.push_back(USA);
//    list.push_back(Canada);
//    list.push_back(Mexico);
//    list.push_back(Cuba);
//    Continent continent = Continent(0,"NA",2,list);
//    vector<Territory*> player1list;
//    player1list.push_back(USA);
//    player1list.push_back(Mexico);
//    vector<Territory*> player2list;
//    player2list.push_back(Canada);
//    player2list.push_back(Cuba);
//    player1=new Player("player1",player1list);
//    player2=new Player("player2",player2list);
//
//    Deploy* ddd=new Deploy(player1,USA,5);
//    ddd->execute();
//    Advance* aaa=new Advance(player1,USA,Canada,3);
//    aaa->execute();
//    Bomb* bbb= new Bomb(player1,Canada);
//    bbb->execute();
//    Blockade* ccc=new Blockade(player2,Canada);
//    ccc->execute();
//    Airlift* fff=new Airlift(player1,USA,Mexico,5);
//    fff->execute();
//
//
//    USA->~Territory();
//    Mexico->~Territory();
//    Canada->~Territory();
//    Cuba->~Territory();
//    ddd->~Deploy();
//    aaa->~Advance();
//    bbb->~Bomb();
//    ccc->~Blockade();
//    fff->~Airlift();
//    cout<<"__________________test issuse order phase_________________________"<<endl;
//
//    Player* player1;
//    Player* player2;
//    Territory* USA =new Territory(1,"USA", 10, "player1",0,"NA");
//    Territory* Canada =new Territory(2,"Canada", 10, "player2",0,"NA");
//    Territory* Mexico =new Territory(3,"Mexico", 10, "player1",0,"NA");
//    Territory* Cuba =new Territory(4,"Cuba", 10, "player2",0,"NA");
//
//    TerritoryList.push_back(USA);
//    TerritoryList.push_back(Canada);
//    TerritoryList.push_back(Mexico);
//    TerritoryList.push_back(Cuba);
//    Continent continent = Continent(0,"NA",2,TerritoryList);
//    vector<Territory*> player1list;
//    player1list.push_back(USA);
//    player1list.push_back(Mexico);
//    vector<Territory*> player2list;
//    player2list.push_back(Canada);
//    player2list.push_back(Cuba);
//    player1=new Player("player1",player1list);
//    player2=new Player("player2",player2list);
//
//    PlayerList.push_back(player1);
//    PlayerList.push_back(player2);
//    GameLoop gameloop;
//    gameloop.IssueOrderPhase();











}
