//
// Created by Jingyi on 2021-02-05.
//

#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>

using namespace std;

MapLoader::MapLoader(const MapLoader &ml): file(ml.file) {
    this->GameMap=ml.GameMap;
    this->file=ml.file;
    this->lshape=ml.lshape;
    this->number_of_mapboard=ml.number_of_mapboard;
    this->number_of_regions=ml.number_of_regions;
    this->number_of_continents=ml.number_of_continents;
}

MapLoader ::MapLoader(string filename): file(filename) {
    this->GameMap = new Map("Game 1");
    string line;
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
                    this->number_of_mapboard=stoi(line.substr(mapboard.size(),line.size()),nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for mapboard");
                }

            }
            else if(line.find(continent)!=string::npos){
                try{
                    this->number_of_continents=stoi(line.substr(continent.size(),line.size()),nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for continent");
                }
            }
            else if(line.find(region)!=string::npos){
                try{
                    this->number_of_regions=stoi(line.substr(region.size(),line.size()), nullptr,10);
                }
                catch (std::exception& e){
                    throw std::string("Cannot convert string to integer for regions");
                }

            }
            else if(line.find("shape=")!=string::npos){
                this->lshape=line.substr(6,line.size()).compare("l")==0;
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

    string deliminater = " ";
    size_t pos = 0;
    string token;
    string temp;
    HelperFunctionMap helper;
    //GameMap->CreateCountryMatrix(number_of_regions);
    //GameMap->CreateContinentMatrix(number_of_continents);
    int mapid,continentid,regionid;
    int column=0;

    //hashing map board name
    std::unordered_map<int,string> map_hashmap;

    //Use to store split input line
    vector<string> vector_temp;

    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);
        this->split(temp,deliminater,vector_temp);
        mapid = stoi(vector_temp[0], nullptr,10);
        if(mapid<-1 || mapid>=number_of_mapboard)
            throw std::string("map board id is invalid");
        map_hashmap.insert(std::make_pair(mapid,vector_temp[1]));
        vector_temp.clear();
    }

    //continentid,mapid
    std::unordered_map<int,int> map_continent_hashmap;
    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);

        //split temp token
        this->split(temp,deliminater,vector_temp);

        //First entry is continent id
        continentid = stoi(vector_temp[0], nullptr,10);
        if(continentid<-1 || continentid>=number_of_continents)
            throw std::string("continent id is invalid");

        //Second entry is continent name
        GameMap->AddContinent(new Continent(vector_temp[1],continentid));

        //Third entry is map board id
        mapid=stoi(vector_temp[2], nullptr,10);
        if(mapid<-1 || mapid>=number_of_mapboard)
            throw std::string("map board id is invalid");
        map_continent_hashmap.insert(make_pair(continentid,mapid));
        vector_temp.clear();
    }

    string region_name,continent_name;
    string delimiter_comma=",",temp_edge;
    int connected_regionid;
    std::unordered_map<int,Territory*> Territory_buffer;
    std::unordered_map<int,vector<int>> connection_vector_hashmap;
    std::vector<pair<int,int>> out_nodes;

    for(int i=0;i<regions_buffer.size();i++){
        temp=regions_buffer.at(i);
        while ((pos = temp.find(deliminater)) != std::string::npos) {
            token = temp.substr(0, pos);
            if(column==0) {
                regionid = stoi(token, nullptr, 10);
                if(regionid<-1 || regionid>=number_of_regions)
                    throw std::string("Territory/region id is invalid");
                connection_vector_hashmap.insert(std::make_pair(regionid,vector<int>()));
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
                    connection_vector_hashmap[regionid].push_back(connected_regionid);
                    token.erase(0,pos+delimiter_comma.length());
                }
                connected_regionid=stoi(token, nullptr,0);
                if(connected_regionid<=-1||connected_regionid>=number_of_regions)
                    throw std::string("Connected Territory id is invalid");
                connection_vector_hashmap[regionid].push_back(connected_regionid);
                //cout << "last connected id:"<<token<<endl;
                //helper.AddEdgesCountry();
            }
            else if(column==4){
                Territory_buffer.insert(std::make_pair(regionid,new Territory(region_name,regionid,continentid)));
            }
            column++;
            temp.erase(0, pos + deliminater.length());
        }
        if(column==2)
            throw std::string("Missing information in [regions]");
        else if(column==3){
            while ((pos = token.find(delimiter_comma)) != std::string::npos) {
                temp_edge=token.substr(0, pos);
                connected_regionid=stoi(temp_edge, nullptr,10);
                if(connected_regionid<=-1||connected_regionid>=number_of_regions)
                    throw std::string("Connected Territory id is invalid");
                connection_vector_hashmap[regionid].push_back(connected_regionid);
                token.erase(0,pos+delimiter_comma.length());
            }
            connected_regionid=stoi(token, nullptr,0);
            if(connected_regionid<=-1||connected_regionid>=number_of_regions)
                throw std::string("Connected Territory id is invalid");
            connection_vector_hashmap[regionid].push_back(connected_regionid);
            Territory_buffer.insert(std::make_pair(regionid,new Territory(region_name,regionid,continentid)));
        }
        else{
            while ((pos = temp.find("-out")) != std::string::npos) {
                mapid=stoi(temp.substr(pos-1,pos), nullptr,10);
                if(mapid<=-1||mapid>=this->number_of_mapboard)
                    throw std::string("Map board id is invalid");
                out_nodes.push_back(std::make_pair(mapid,regionid));
                temp.erase(0,pos+delimiter_comma.length());
            }

        }


        column=0;
    }

    for(int index=0;index<number_of_regions;index++){
        this->GameMap->ReturnContinentHashMap()[Territory_buffer[index]->GetContinentNumber()]->AddTerritory(Territory_buffer[index]);
        for(int regionid = 0;regionid<connection_vector_hashmap[index].size();regionid++){
            //each region connected to node index
            helper.AddEdgesCountry(Territory_buffer[index],Territory_buffer[connection_vector_hashmap[index].at(regionid)]);
        }
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_map(0,3);

    std::vector<int> maporder;
    std::vector<int>::iterator it;
    for(int i = 0,temp;i<number_of_mapboard;i++){
        temp=dist_map(mt);
        it = find (maporder.begin(), maporder.end(), temp);
        if(it != maporder.end()){
            i--;
        }
        else
            maporder.push_back(temp);
    }

    std::uniform_int_distribution<int> dist_out(0,out_nodes.size()-1);
    bool find= false;
    for(int i = 0,map1,map2,temp,temp2;i<maporder.size()-1;i++){
        map1=maporder.at(i);
        map2=maporder.at(i+1);
        for(int j = 0;j<out_nodes.size();j++){
            if(out_nodes.at(i).first==map1){
                temp=out_nodes.at(i).second;
                out_nodes.erase(out_nodes.begin()+i);
                break;
            }
        }
        while(!find){
            temp2=dist_out(mt);
            if(out_nodes.at(temp2).first==map2){
                helper.AddEdgesCountry(Territory_buffer[temp],Territory_buffer[temp2]);
                out_nodes.erase(out_nodes.begin()+temp2);
                break;
            }
        }
    }



}

std::ostream& operator<<(ostream& output, MapLoader * mapLoader) {

    //Print the shape of map, map board, number of continents, number of node
    //number of regions
    output<< "MapLoader is loading game board from:"<<endl;
    output<<mapLoader->getFile()<<"."<<endl;
    if(mapLoader->getLshape())
        output<<"This Map is L shaped."<<endl;
    else
        output<<"This Map is long rectangle shaped."<<endl;
    output << "The map has " << mapLoader->getNumberofmapboard() <<" map boards"<<endl;
    output << "The number of continents: "<<mapLoader->getNumberofcontinents()<<endl;
    output << "The number of territory: "<<mapLoader->getNumberofregions()<<endl;
    return output;
}

void MapLoader::split( string input, const string& deliminater, vector<string>& result) {
    int pos;
    string token;
    while ((pos = input.find(deliminater)) != std::string::npos) {
        token = input.substr(0, pos);
        result.push_back(token);
        input.erase(0, pos + deliminater.length());
    }
    result.push_back(input);
}

string MapLoader::getFile() {return this->file;}

Map * MapLoader::getGameMap() {
    return this->GameMap;
}

int MapLoader::getNumberofmapboard(){return this->number_of_mapboard;}
int MapLoader::getNumberofcontinents() {return this->number_of_continents;}
int MapLoader::getNumberofregions() {return this->number_of_regions;}

bool MapLoader::getLshape(){return this->lshape;}

