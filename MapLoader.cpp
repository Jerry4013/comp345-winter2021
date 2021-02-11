//
// Created by Jingyi on 2021-02-05.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

MapLoader ::MapLoader() {
    this->GameMap= nullptr;
}

MapLoader::MapLoader(const MapLoader &ml): file(ml.file) {
    this->GameMap=ml.GameMap;
}

MapLoader ::MapLoader(string filename): file(filename) {
    this->GameMap = new Map("Game 1");
    string line;
    ifstream map_file (filename);
    vector<string> regions_buffer,continent_buffer,map_buffer;
    bool continents=false,regions=false,map=false;

    //read map file
    if (map_file.is_open())
    {
        while ( getline (map_file,line) )
        {
            if(line.find("[continents]")!=string::npos){
                //Look for the contents, should be continents or regions
                continents=true;
                regions=false;
                map=false;
            }
            else if(line.find("[regions]")!=string::npos){
                continents=false;
                regions=true;
                map=false;
            }
            else if(line.find("[map]")!=string::npos){
                continents=false;
                regions=false;
                map=true;
            }
            else if(line.find("//")==string::npos){
                if(continents){
                    continent_buffer.push_back(line);
                }
                else if(regions){
                    regions_buffer.push_back(line);
                }
                else if(map){
                    map_buffer.push_back(line);
                }
            }


        }
        map_file.close();
    }
    else
        throw 25; //if the program cannot open the file throw error code 25;


    string delimiter = " ";
    size_t pos = 0;
    string token;
    string temp;
    HelperFunctionMap helper;
    //GameMap->CreateCountryMatrix();
    GameMap->CreateContinentMatrix();
    int id;
    int column=0;
  /*
    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);

        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            std::cout << token << std::endl;
            temp.erase(0, pos + delimiter.length());
        }

        cout<<temp<<endl;
    }
    */
    cout <<endl;
    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0){
                id = stoi(token, nullptr,10);
            }
            else if(column==1){
                GameMap->AddContinent(new Continent(token,id));
            }
            temp.erase(0, pos + delimiter.length());
            column++;
        }
        column=0;
    }

    cout <<endl;
    column=0;
    string region_name,continent_name;
    int continent_id;
    for(int i=0;i<regions_buffer.size();i++){
        temp=regions_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0) {
                id = stoi(token, nullptr, 10);
            }
            else if(column==1){
                region_name=token;
            }
            else if(column==2){
                continent_id=stoi(token, nullptr,10);
                for(int i =0;i<this->GameMap->ReturnContient().size();i++){
                    if (this->GameMap->ReturnContient().at(i)->GetContinentNum()==continent_id)
                        this->GameMap->ReturnContient().at(i)->AddTerritory(new Territory(region_name,id,this->GameMap->ReturnContient().at(i)->GetContinentName()));
                }
            }
            temp.erase(0, pos + delimiter.length());
            column++;
        }
        column=0;
        //cout<<temp<<endl<<endl;
    }

}

std::ostream& operator<<(ostream& output, MapLoader mapLoader) {
    //output<<"MapLoader buffer: "<<mapLoader.getMap()<<endl;
    return output;
}

Map * MapLoader::getGameMap() {
    return this->GameMap;
}
