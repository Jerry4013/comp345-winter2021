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
    string shape;
    ifstream mapfile (filename);
    string map_order_buffer;
    vector<string> regions_buffer,continent_buffer,map_buffer;
    bool continents=false,regions=false,map=false,map_order=false;
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
            else if(shape.empty()){
                int found = line.find("shape=");
                //cout << found <<endl;
                if (found != string::npos)
                    shape=line.substr(6,line.size());
            }

            if(line.find("[continents]")!=string::npos){
                //Look for the contents, should be continents or regions
                continents=true;
                regions=false;
                map=false;
                map_order=false;
            }
            else if(line.find("[regions]")!=string::npos){
                continents=false;
                regions=true;
                map=false;
                map_order=false;
            }
            else if(line.find("[map]")!=string::npos){
                continents=false;
                regions=false;
                map=true;
                map_order=false;
            }
            else if(line.find("[map_order]")!=string::npos){
                continents=false;
                regions=false;
                map=false;
                map_order=true;
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
                else if(map_order){
                    map_order_buffer+=line;
                }
            }


        }
        mapfile.close();
    }
    else
        throw 20;

    /*
    cout<< "continents:"<<numberofcontinents<<endl;
    cout<< "regions:"<<numberofregions<<endl;
    cout << "shape:"<<shape<<endl;
    cout << "maps:"<<map_buffer<<endl;
    cout << "map order:"<<map_order_buffer<<endl;
    cout<<continent_buffer<<endl;
    cout<<regions_buffer<<endl;
     */

    string delimiter = " ";
    size_t pos = 0;
    string token;
    string temp;
    for(int i=0;i<map_buffer.size();i++){
        temp=map_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            std::cout << token << std::endl;
            temp.erase(0, pos + delimiter.length());
        }
        cout<<temp<<endl;
    }
    cout <<endl;
    for(int i=0;i<continent_buffer.size();i++){
        temp=continent_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            std::cout << token << std::endl;
            temp.erase(0, pos + delimiter.length());
        }
        cout<<temp<<endl<<endl;
    }
    cout <<endl;
    for(int i=0;i<regions_buffer.size();i++){
        temp=regions_buffer.at(i);
        while ((pos = temp.find(delimiter)) != std::string::npos) {
            token = temp.substr(0, pos);
            std::cout << token << std::endl;
            temp.erase(0, pos + delimiter.length());
        }
        cout<<temp<<endl<<endl;
    }
}

std::ostream& operator<<(ostream& output, MapLoader mapLoader) {
    //output<<"MapLoader buffer: "<<mapLoader.getMap()<<endl;
    return output;
}

Map * MapLoader::getMapptr() {
    return this->GameMap;
}