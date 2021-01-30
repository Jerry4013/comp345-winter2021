#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "Map.h"
#include <map>

extern string ContinentNameFromMap[];
extern int ContinentBonusFromMap[];

extern int ContriesNumberFromMap[];
extern string ContriesNameFromMap[];
extern int ContriesNumberBelongsToContinents[];

extern int ConnectionBufferFromMap[100][100];


class MapLoader
{
private:
    std::vector<Continent> continentVector;
public:
    void loadMap(std::string fileName);
    std::string line;
    int lineCount;
    int continentsStartLine;
    int countriesStartLine;
    int bordersStartLine;
    int EndofFileLine;
    int CountryNum;
    int TheContinentBelongToNum;
    string CountryName;
    string Continentbuffer[3];
    string Countrybuffer[3];
    int ConnectionBuffer[100];
    int NumberOfWhiteSpace;
    int ArmyWorth;
    string continentName;
};

class ConquestFileReader {
public:
    ConquestFileReader();
    ConquestFileReader(string);
    ~ConquestFileReader();
    void conquestLoadMap(string);
    string getInputConquestFileName();
    void setInputConquestFileName(string);
    string inputConquestFileName;
};

class ConquestFileReaderAdapter : public MapLoader {
public:
    ConquestFileReaderAdapter();
    ConquestFileReaderAdapter(const ConquestFileReaderAdapter*);
    ConquestFileReaderAdapter(string, int);
    ~ConquestFileReaderAdapter();
    ConquestFileReader conquestFileReader;
};

