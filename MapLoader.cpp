//
// Created by lllll on 2021-02-05.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MapLoader ::MapLoader() {
    this->GameMap= nullptr;
}

MapLoader ::MapLoader(string filename) {
    string line;
    int numberofcontinents = -1,numberofregions=-1;
    ifstream mapfile (filename);
    string regionsbuffer,continentbuffer;
    bool continents=false,regions=false;
    if (mapfile.is_open())
    {
        while ( getline (mapfile,line) )
        {
            if(numberofcontinents==-1){
                int found = line.find("numberofcontinents=");
                //cout << line.substr(19, line.size())<<endl;
                if (found != string::npos)
                    numberofcontinents=stoi(line.substr(19, line.size()),nullptr,0);
            }
            else if(numberofregions==-1){
                int found = line.find("numberofregions=");
                //cout << found <<endl;
                if (found != string::npos)
                    numberofregions=stoi(line.substr(16, line.size()),nullptr,0);
            }

            if(line.find("[continents]")!=string::npos){
                //Look for the contents, should be continents or regions
                continents=true;
                regions=false;
            }
            else if(line.find("[regions]")!=string::npos){
                continents=false;
                regions=true;
            }
            else if(line.find("//")==string::npos){
                if(continents){
                    continentbuffer+=line;
                    continentbuffer+="\n";
                }
                else if(regions){
                    regionsbuffer+=line;
                    regionsbuffer+="\n";
                }
            }


        }
        mapfile.close();
    }
    else
        throw 20;

    cout<< "continents:"<<numberofcontinents<<endl;
    cout<< "regions:"<<numberofregions<<endl;
    cout<<continentbuffer<<endl;
    cout<<regionsbuffer<<endl;

}

std::ostream& operator<<(ostream& output, MapLoader mapLoader) {
    //output<<"MapLoader buffer: "<<mapLoader.getMap()<<endl;
    return output;
}

Map * MapLoader::getMapptr() {
    return this->GameMap;
}