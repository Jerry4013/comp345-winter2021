
#include <fstream>
#include <sstream>
#include "MapLoader.h"

using namespace std;

string ContinentNameFromMap[100];
int ContinentBonusFromMap[100];

int ContriesNumberFromMap[100];
string ContriesBelongsToContinentsFromMap[100];
int ContriesNumberBelongsToContinents[100];

int ConnectionBufferFromMap[100][100];

void MapLoader::loadMap(std::string fileName) {
    std::ifstream fileIfStream;
    std::ifstream fileIfStreamtwo;
    string Continentbuffer[3];
    string Countrybuffer[3];
    int ConnectionBuffer[100];
    for (int i = 0; i < 100; i++) {
        ConnectionBuffer[i] = 0;
        ContinentBonusFromMap[i]=0;
        ContriesNumberBelongsToContinents[i]=0;
        ContriesBelongsToContinentsFromMap[i]="NONE";
        ContinentNameFromMap[i]="NONE";
        ContriesNumberFromMap[i]=0;
        for (int j = 0; j < 100; j++){
            ConnectionBufferFromMap[i][j]=0;
        }

    }
    string line;
    int lineCount = 0;

    //continent
    string continentName;

    //country

    string CountryName = "";
    //borders




    int continentsStartLine;
    int countriesStartLine;
    int bordersStartLine;
    int EndofFileLine;
    //create map object





    //check if file can be opened
    fileIfStream.open(fileName);
    while (fileIfStream) {
        getline(fileIfStream, line);
        lineCount++;
        if (line.find("[continents]") != string::npos) {
            continentsStartLine = lineCount;
//            cout <<continentsStartLine<<endl;
        }
        if (line.find("[countries]") != string::npos) {
            countriesStartLine = lineCount;
//            cout <<countriesStartLine<<endl;
        }
        if (line.find("[borders]") != string::npos) {
            bordersStartLine = lineCount;
//            cout <<bordersStartLine<<endl;
        }
        if (line.empty()) {
            EndofFileLine = lineCount;
//            cout <<EndofFileLine<<endl;
            fileIfStream.close();
        }

    }



    fileIfStreamtwo.open(fileName);
    lineCount = 0;
    while (fileIfStreamtwo) {
        getline(fileIfStreamtwo, line);
        lineCount++;
        //continents name get continents army worth get
        if (lineCount > continentsStartLine && lineCount < countriesStartLine) {
            stringstream ssin(line);
            int i = 0;
            while (ssin.good() && i <= 2) {
                ssin >> Continentbuffer[i];
                ++i;
            }
            //test
//                        for (i = 0; i < 3; i++) {
//                cout << Continentbuffer[i] << endl;
//            }
            for(int i = 0;i<countriesStartLine-continentsStartLine-2 ; i++){
                if(ContinentNameFromMap[i]=="NONE"){
                    ContinentNameFromMap[i]=Continentbuffer[0];
                    break;
                }
            }
            for(int i = 0;i<countriesStartLine-continentsStartLine-2 ; i++){
                if(ContinentBonusFromMap[i]==0){
                    ContinentBonusFromMap[i]=stoi(Continentbuffer[1]);
                    break;
                }
            }
            //test
//            for(int i = 0;i<10 ; i++){
//                    cout << "The continent " << ContinentNameFromMap[i] << " has " << ContinentBonusFromMap[i]
//                         << " Bonus"<< endl;
//            }
        }



        //country buffer
        if (lineCount > countriesStartLine && lineCount < bordersStartLine) {
            stringstream ssin(line);
            int i = 0;
            while (ssin.good() && i <= 3) {
                ssin >> Countrybuffer[i];
                ++i;
            }
            //test
//            for (i = 0; i < 3; i++) {
//                cout << Countrybuffer[i] << endl;
//            }
            for(int i = 0;i<bordersStartLine-countriesStartLine-2 ; i++){
                if(ContriesNumberFromMap[i]==0){
                    ContriesNumberFromMap[i]=stoi(Countrybuffer[0]);
                    break;
                }
            }
            for(int i = 0;i<bordersStartLine-countriesStartLine-2 ; i++){
                if(ContriesBelongsToContinentsFromMap[i]=="NONE"){
                    ContriesBelongsToContinentsFromMap[i]=Countrybuffer[1];
                    break;
                }
            }
            for(int i = 0;i<bordersStartLine-countriesStartLine-2 ; i++){
                if(ContriesNumberBelongsToContinents[i]==0){
                    ContriesNumberBelongsToContinents[i]=stoi(Countrybuffer[2]);
                    break;
                }
            }

            //test
//            for(int i = 0;i<100 ; i++){
//                    cout << "The country number is" << ContriesNumberFromMap[i] << " Contrie name is: " << ContriesBelongsToContinentsFromMap[i]
//                    <<"The coutrie belong to this continent : "<< ContriesNumberBelongsToContinents[i]<<endl;
//            }


        }

        //connection between country
        if (lineCount > bordersStartLine && lineCount < EndofFileLine) {
            stringstream ssin(line);
            int i = 0;
            while (ssin.good() && i < 100 && !line.empty()) {
                ssin >> ConnectionBuffer[i];
                ++i;
            }

            //clear buffer
//            for (i = 0; i < 15; i++) {
//                cout <<  ConnectionBuffer[i]<< " ";
//            }

            for(int i = 0;i<50;i++){
                if(ConnectionBuffer[i+1]!=0) {
                    ConnectionBufferFromMap[ConnectionBuffer[0]][ConnectionBuffer[i + 1]] = 1;
                }
            }
            //test
//            for(int i = 0;i<30;i++){
//                for(int j = 0;j<30;j++){
//                    cout <<ConnectionBufferFromMap[i][j]<<" ";
//                }
//                cout << endl;
//            }

            //clear buffer
            for (i = 0; i < 10; i++) {
                 ConnectionBuffer[i]=0;
            }

        }


        if (line.empty()) {
            fileIfStreamtwo.close();
        }
    }


}




