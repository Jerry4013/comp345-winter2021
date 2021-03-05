//
// Created by Luojia yan on 2021-02-07.
//

#include "Map.h"
using namespace std;
#include "iostream"
#include "MapDriver.h"

int mapDriver::main() {
    vector<string> mapNames = {"volcano", "redForest", "village", "mountain"};

    vector<string> continentNames = {"volcano1", "volcano2", "redForest", "village", "mountain1", "mountain2"};
    vector<int> belongsToMapId = {1, 1, 2, 3, 4, 4};

    vector<string> territoryNames = {"volcano1_upper1", "volcano1_upper2", "volcano2_upper", "volcano2_middle1",
                                     "volcano2_middle2", "volcano2_bottom1", "volcano2_bottom2", "redforest_upper",
                                     "redforest_middle", "redforest_bottom", "village_upper1", "village_upper2",
                                     "village_middle", "village_bottom1", "village_bottom2", "mountain1_upper",
                                     "mountain1_middle", "mountain2"};
    vector<int> belongsToContinentId = {1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 6};
    vector<vector<int>> edges = {{1, 2}, {2, 5}, {3, 4}, {3, 5}, {4, 5}, {5, 6}, {6, 7}, {4, 9}, {8, 9}, {9, 10},
                                 {7, 11}, {11, 12}, {11, 13}, {12, 13}, {12, 14}, {13, 14}, {14, 15}, {13, 16},
                                 {16, 17}, {17, 18}, {10, 16}};

    string mapName = "testMap";
    Map* testMap1 = new Map(1, mapName);
    vector<Continent*> continents(continentNames.size());
    for (int i = 0; i < continents.size(); i++) {
        continents[i] = new Continent(i + 1, continentNames[i], belongsToMapId[i]);
        testMap1->addContinent(continents[i]);
    }

    vector<Territory*> territories(territoryNames.size());
    for (int i = 0; i < territories.size(); i++) {
        territories[i] = new Territory(i + 1, territoryNames[i], belongsToContinentId[i], 2);
        continents[belongsToContinentId[i] - 1]->addTerritory(territories[i]);
        testMap1->addTerritory(territories[i]);
    }
    for (auto & edge : edges) {
        testMap1->addTerritoryEdges(edge[0], edge[1]);
    }
    cout << *testMap1 << endl;
    // TODO: need more tests
    return 0;

}
