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
    GameMap->CreateCountryMatrix();
    GameMap->CreateContinentMatrix();
    int mapid,continentid,regionid;
    int column=0;

    //Use to store split input line
    vector<string> vector_temp;

    //processing [map] data
    //First split the data into mapid,mapname. Then use these two map to create an hashmap
    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);
        this->split(temp,deliminater,vector_temp);
        mapid = stoi(vector_temp[0], nullptr,10);
        if(mapid<0 || mapid>number_of_mapboard)
            throw std::string("map board id is invalid");
        vector_temp.clear();
    }

    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);

        //split temp token
        this->split(temp,deliminater,vector_temp);

        //First entry is continent id
        continentid = stoi(vector_temp[0], nullptr,10);
        if(continentid<0 || continentid>number_of_continents)
            throw std::string("continent id is invalid");

        //Second entry is continent name
        this->GameMap->AddContinent(new Continent(vector_temp[1],continentid));

        //Third entry is map board id
        mapid=stoi(vector_temp[2], nullptr,10);
        if(mapid<0 || mapid>number_of_mapboard)
            throw std::string("map board id is invalid");
        vector_temp.clear();
    }

    string continent_name;
    string deliminater_comma=",",temp_edge;
    std::unordered_map<int,Territory*> Territory_buffer;
    std::unordered_map<int,vector<int>> connection_vector_hashmap;
    std::vector<pair<int,int>> out_nodes;
    vector<int> mapoutnodes;

    for(int i=0;i<regions_buffer.size();i++){
        temp=regions_buffer.at(i);
        this->split(temp,deliminater,vector_temp);
        if(vector_temp.size()<4)
            throw std::string("Missing information in [regions]");

        //First entry, regionid
        regionid = stoi(vector_temp[0], nullptr, 10);
        if(regionid<0 || regionid>number_of_regions)
            throw std::string("Territory/region id is invalid");
        connection_vector_hashmap.insert(std::make_pair(regionid,vector<int>()));

        //Second entry, region name
        //Thrid entry, continentid
        continentid=stoi(vector_temp[2], nullptr,10);
        if(continentid<0 || continentid>number_of_continents)
            throw std::string("Continent id is invalid");

        Territory_buffer.insert(make_pair(regionid,new Territory(vector_temp[1],regionid,continentid)));

        //Fourth entry, connected node
        this->split(vector_temp[3],deliminater_comma,connection_vector_hashmap[regionid]);

        //Fifth entry, if out nodes
        if(vector_temp.size()==5){
            this->split(vector_temp[4],deliminater_comma,mapoutnodes);
            for(int i:mapoutnodes){
                out_nodes.push_back(make_pair(regionid,i));
            }
            mapoutnodes.clear();
        }
        vector_temp.clear();
    }

    for(int index=1;index<=number_of_regions;index++){
        continentid=Territory_buffer[index]->GetContinentNumber();
        this->GameMap->ReturnContinentHashMap()[continentid]->AddTerritory(Territory_buffer[index]);
        for(int regionid = 0;regionid<connection_vector_hashmap[index].size();regionid++){
            helper.AddEdgesCountry(Territory_buffer[index],Territory_buffer[connection_vector_hashmap[index].at(regionid)]);
        }
    }

    connection_vector_hashmap.clear();

    std::random_device rd;
    std::seed_seq seed{rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd()};
    std::mt19937 mt(seed);

    std::uniform_int_distribution<int> dist_map(1,number_of_mapboard);
    std::vector<int> maporder;
    std::vector<int>::iterator it;

    for(int i = 0,temp;i<number_of_mapboard;i++){
        temp=dist_map(mt);
        it = find (maporder.begin(), maporder.end(), temp);
        if(it != maporder.end()){
            i--;
        }
        else{
            maporder.push_back(temp);
            this->mapboard_order+=to_string(temp);
        }
    }

    std::uniform_int_distribution<int> dist_out(0,out_nodes.size()-1);
    bool find= false;
    for(int i = 0,map1,map2,temp,temp2;i<maporder.size()-1;i++){
        map1=maporder.at(i);
        map2=maporder.at(i+1);
        for(int j = 0;j<out_nodes.size();j++){
            if(out_nodes.at(j).second==map1){
                //region id
                temp=out_nodes.at(j).first;
                out_nodes.erase(out_nodes.begin()+j);
                break;
            }
        }
        while(true){
            temp2=dist_out(mt)%out_nodes.size();
            if(out_nodes.at(temp2).second==map2){
                helper.AddEdgesCountry(Territory_buffer[temp],Territory_buffer[out_nodes.at(temp2).first]);
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
    output << "The map board order: "<<mapLoader->mapboard_order<<endl;
    return output;
}

//Split into string vector
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
//Split into int vector
void MapLoader::split( string input, const string& deliminater, vector<int>& result) {
    int pos;
    string token;
    while ((pos = input.find(deliminater)) != std::string::npos) {
        token = input.substr(0, pos);
        result.push_back(stoi(token, nullptr,10));
        input.erase(0, pos + deliminater.length());
    }
    if(!input.empty())
        result.push_back(stoi(input, nullptr,10));
}
string MapLoader::getFile() {return this->file;}
Map * MapLoader::getGameMap() {return this->GameMap;}
int MapLoader::getNumberofmapboard(){return this->number_of_mapboard;}
int MapLoader::getNumberofcontinents() {return this->number_of_continents;}
int MapLoader::getNumberofregions() {return this->number_of_regions;}
bool MapLoader::getLshape(){return this->lshape;}

