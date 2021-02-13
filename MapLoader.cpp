//
// Created by Jingyi on 2021-02-05.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

MapLoader ::MapLoader() {
    this->GameMap= nullptr;
    file="";
}

MapLoader::MapLoader(const MapLoader &ml): file(ml.file) {
    this->GameMap=ml.GameMap;
}

MapLoader ::MapLoader(string filename): file(filename) {
    this->GameMap = new Map("Game 1");
    string line;
    int number_of_mapboard=-1;
    bool Lshape=false;
    int number_of_continents=-1,number_of_regions=-1;
    ifstream map_file (filename);
    vector<string> regions_buffer,continent_buffer,map_buffer;
    bool continents=false,regions=false,map=false;

    const string mapboard="numberofmapboards=",continent="numberofcontinents=",region="numberofregions=";
    //read map file
    if (map_file.is_open())
    {
        while ( getline (map_file,line) )
        {
            std::transform(line.begin(), line.end(), line.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            if(line.find(mapboard)!=string::npos){
                try{
                    number_of_mapboard=stoi(line.substr(mapboard.size(),line.size()),nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for mapboard");
                }

            }
            else if(line.find(continent)!=string::npos){
                try{
                    number_of_continents=stoi(line.substr(continent.size(),line.size()),nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for continent");
                }
            }
            else if(line.find(region)!=string::npos){
                try{
                    number_of_regions=stoi(line.substr(region.size(),line.size()), nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for regions");
                }

            }
            else if(line.find("shape=")!=string::npos){
                Lshape=line.substr(6,line.size()).compare("l")==0;
            }
            else if(line.find("[continents]")!=string::npos){
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
                else{
                    throw std::string("Invalid map file format");
                }
            }


        }
        map_file.close();
    }
    else
        throw std::string("Map file does not exist in the path"); //if the program cannot open the file throw error message;

    if(number_of_regions==-1 || number_of_continents==-1
        || number_of_mapboard==-1 )
        throw std::string("Missing number of regions, continents or mapboard");
    else if(number_of_regions!=regions_buffer.size() || number_of_continents!=continent_buffer.size()
        || number_of_mapboard!=map_buffer.size())
        throw std::string("Unmatched number of data");

    string delimiter = " ";
    size_t pos = 0;
    string token;
    string temp;
    HelperFunctionMap helper;
    //GameMap->CreateCountryMatrix(number_of_regions);
    //GameMap->CreateContinentMatrix(number_of_continents);
    int mapid,continentid,regionid;
    int column=0;

    std::unordered_map<int,string> map_hashmap;
    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);

        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0){
                mapid=stoi(token,nullptr,10);
                if(mapid<-1 || mapid>=number_of_mapboard)
                    throw std::string("map board id is invalid");
            }
            else if(column==1)
                map_hashmap.insert(std::make_pair(mapid,token));
            temp.erase(0, pos + delimiter.length());
            column++;
        }
        column=0;
    }

    column=0;
    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0){
                continentid = stoi(token, nullptr,10);
                if(continentid<-1 || continentid>=number_of_continents)
                    throw std::string("continent id is invalid");
            }
            else if(column==1){
                GameMap->AddContinent(new Continent(token,continentid));
            }
            else if(column==2){
                mapid=stoi(token, nullptr,10);
                if(mapid<-1 || mapid>=number_of_mapboard)
                    throw std::string("map board id is invalid");
            }
            temp.erase(0, pos + delimiter.length());
            column++;
        }
        column=0;
    }

    column=0;
    string region_name,continent_name;
    bool outnode=false;
    string delimiter_comma=",",temp_edge;
    int connected_regionid;
    std::unordered_map<int,Territory*> Territory_buffer;
    std::unordered_map<int,vector<int>> Territory_connection_map;

    for(int i=0;i<regions_buffer.size();i++){
        temp=regions_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0) {
                regionid = stoi(token, nullptr, 10);
                if(regionid<-1 || regionid>=number_of_regions)
                    throw std::string("Territory/region id is invalid");
                Territory_connection_map.insert(std::make_pair(regionid,vector<int>()));
            }
            else if(column==1){
                region_name=token;
            }
            else if(column==2){
                continentid=stoi(token, nullptr,10);
                if(continentid<-1 || continentid>=number_of_continents)
                    throw std::string("Continent id is invalid");
            }
            else if(column==3){
                while ((pos = token.find(delimiter_comma)) != std::string::npos) {
                    temp_edge=token.substr(0, pos);
                    connected_regionid=stoi(temp_edge, nullptr,10);
                    if(connected_regionid<=-1||connected_regionid>=number_of_regions)
                        throw std::string("Connected Territory id is invalid");
                    Territory_connection_map[regionid].push_back(connected_regionid);
                    token.erase(0,pos+delimiter_comma.length());
                }
                connected_regionid=stoi(token, nullptr,0);
                if(connected_regionid<=-1||connected_regionid>=number_of_regions)
                    throw std::string("Connected Territory id is invalid");
                Territory_connection_map[regionid].push_back(connected_regionid);
                //cout << "last connected id:"<<token<<endl;
                //helper.AddEdgesCountry();
            }
            else if(column==4){
                Territory_buffer.insert(std::make_pair(regionid,new Territory(region_name,regionid,continentid)));
                outnode=true;
            }
            column++;
            temp.erase(0, pos + delimiter.length());

        }
        column=0;
    }

    for(int index=0;index<number_of_regions;index++){
        for(int regionid = 0;regionid<number_of_regions;regionid++){
            //each region connected to node index
            Territory_connection_map[index].at(regionid);
        }
    }


}

std::ostream& operator<<(ostream& output, MapLoader mapLoader) {

    //Print the shape of map, map board, number of continents, number of node
    //number of regions
    output<< "MapLoader is loading game board from:"<<endl;
    output<<mapLoader.getFile()<<endl;

    return output;
}

string MapLoader::getFile() {return this->file;}

Map * MapLoader::getGameMap() {
    return this->GameMap;
}
