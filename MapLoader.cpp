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

MapLoader::MapLoader() {
    this->MapPtr=nullptr;
    this->lshape="";
    this->counter=0;
}

MapLoader::MapLoader(MapLoader *ml) {
    this->MapPtr=ml->MapPtr;
    this->lshape=ml->lshape;
    this->counter=ml->counter;
}

MapLoader ::~MapLoader() {
    delete this->MapPtr;
    this->MapPtr= nullptr;
}

MapLoader::loadMap(string& filePath){
    this->counter++;
    string line;
    ifstream map_file (filename);
    vector<string> regions_buffer,continent_buffer,map_buffer;
    bool continents=false,regions=false,map=false;

    //Look for these tokens in map file
    const string mapboard="numberofmapboards=",continent="numberofcontinents=",region="numberofregions=";
    string mapboard_order;
    int number_of_mapboard=-1,number_of_regions=-1,number_of_continents=-1;
    /*
     * Read map file and store string data in vector<string>
     * If any information is missing, the program will throw an exception
     */
    if (map_file.is_open()){
        while ( getline (map_file,line) )
        {
            //change all characters to lowercase
            std::transform(line.begin(), line.end(), line.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            //must have map board data
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
    
    validateMapFile(map_buffer,continent_buffer,regions_buffer,number_of_mapboard,number_of_continents,number_of_regions);

    Map* GameMap = new Map(this->counter, "GAME "+to_string(this->counter));
    string deliminater = " ";
    string token;
    string temp;
    int mapid,continentid,regionid;

    //Use to store split input line
    vector<string> vector_temp;

    //processing [map] data
    //First split the data into mapid,mapname. Then use these two map to create an hashmap
    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);
        this->split(temp,deliminater,vector_temp);
        mapid = stoi(vector_temp[0], nullptr,10);

        //mapid must be from 1 to number of map board (4 in GAME1.map).
        if(mapid<0 || mapid>number_of_mapboard)
            throw std::string("map board id is invalid");
        vector_temp.clear();
    }


    /*
     * processing [continents] data
     * Retrieve continentid and continent name, and mapid that it belongs to.
     */
    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);

        //split temp token
        this->split(temp,deliminater,vector_temp);

        //First entry is continent id
        continentid = stoi(vector_temp[0], nullptr,10);
        if(continentid<0 || continentid>number_of_continents)
            throw std::string("continent id is invalid");

        //Third entry is map board id
        mapid=stoi(vector_temp[2], nullptr,10);
        if(mapid<0 || mapid>number_of_mapboard)
            throw std::string("map board id is invalid");

        //Second entry is continent name
        GameMap->addContinent(new Continent(continentid,vector_temp[1],mapid));

        vector_temp.clear();
    }

    string continent_name;
    string deliminater_comma=",",temp_edge;
    std::unordered_map<int,Territory*> Territory_buffer;
    std::unordered_map<int,vector<int>> connection_vector_hashmap;
    std::vector<pair<int,int>> out_nodes;
    vector<int> mapoutnodes;

    /*
     * Processing [regions]
     * Regions have 4 or 5 columns
     * Regionid, region_name, continentid, connected nodes, (optional) map out port
     * Because each node must be connect to at least one other node, it must have at least 4 columns.
     */
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

        //Territory_buffer.insert(make_pair(regionid,new Territory(vector_temp[1],regionid,continentid)));

        //Fourth entry, connected node
        this->split(vector_temp[3],deliminater_comma,connection_vector_hashmap[regionid]);

        /*
        * Build map object
        * Add each territory and
        * for each connected nodes, add edges and 
        */
        GameMap->addTerritory(new Territory(regionid, vector_temp[1], continentid, 2))
        for (int i = 0;i<connection_vector_hashmap[regionid].size();i++) {
            GameMap->addTerritoryEdges(regionid,connection_vector_hashmap[regionid][i]);
        }

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

    

    connection_vector_hashmap.clear();

    //Random map generator
    std::random_device rd;
    std::seed_seq seed{rd(),rd(),rd(),rd(),rd(),rd(),rd(),rd()};
    std::mt19937 mt(seed);

    std::uniform_int_distribution<int> dist_map(1,number_of_mapboard);
    std::vector<int> maporder;
    std::vector<int>::iterator it;

    //Map boards are connected randomly for each execution.
    //For example, volcano can be connected to mountain
    //Next execution, volcano could be connected to forest.
    for(int i = 0,temp;i<number_of_mapboard;i++){
        temp=dist_map(mt);
        it = find (maporder.begin(), maporder.end(), temp);
        if(it != maporder.end()){
            i--;
        }
        else{
            maporder.push_back(temp);
            mapboard_order+=to_string(temp);
        }
    }

    //Map's nodes connecting outside map is also chosen randomly
    std::uniform_int_distribution<int> dist_out(0,out_nodes.size()-1);
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
                GameMap->addTerritoryEdges(Territory_buffer[temp],Territory_buffer[out_nodes.at(temp2).first]);
                GameMap->addTerritoryEdges(Territory_buffer[out_nodes.at(temp2).first],Territory_buffer[temp]);
                out_nodes.erase(out_nodes.begin()+temp2);
                break;
            }
        }
    }

    Territory_buffer.clear();
    out_nodes.clear();
    mapoutnodes.clear();
    maporder.clear();
    this->MapPtr=GameMap;
    return GameMap;
}

std::ostream& operator<<(ostream& output, MapLoader * mapLoader) {

    //Print the shape of map, map board, number of continents, number of node
    // //number of regions
    // output<< "MapLoader is loading game board from:"<<endl;
    // output<<mapLoader->getFile()<<"."<<endl;
    // if(mapLoader->getLshape())
    //     output<<"This Map is L shaped."<<endl;
    // else
    //     output<<"This Map is long rectangle shaped."<<endl;
    // output << "The map has " << mapLoader->getNumberofmapboard() <<" map boards"<<endl;
    // output << "The number of continents: "<<mapLoader->getNumberofcontinents()<<endl;
    // output << "The number of territory: "<<mapLoader->getNumberofregions()<<endl;
    // output << "The map board order: "<<mapLoader->mapboard_order<<endl;
    if(this->MapPtr==nullptr)
        output<< "MapLoader did not load any map"<<endl;
    else
        output<< "MapLoader loaded " << this->counter<<" maps."<<endl;
    return output;
}

MapLoader &MapLoader::operator=(const MapLoader &ml) {
    this->GameMap=ml.GameMap;
    this->file=ml.file;
    this->lshape=ml.lshape;
    this->number_of_mapboard=ml.number_of_mapboard;
    this->number_of_regions=ml.number_of_regions;
    this->number_of_continents=ml.number_of_continents;
    return *this;
}

void MapLoader:: validateMapFile(vector<string> map_buffer,vector<string> continent_buffer,vector<string> regions_buffer){
    /*
     * Make sure all the required data are retrieved from map file
     */
    if(number_of_regions==-1 || number_of_continents==-1
       || number_of_mapboard==-1 )
        throw std::string("Missing number of regions, continents or mapboard");
    else if(number_of_regions!=regions_buffer.size() || number_of_continents!=continent_buffer.size()
            || number_of_mapboard!=map_buffer.size())
        throw std::string("Unmatched number of data");
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

