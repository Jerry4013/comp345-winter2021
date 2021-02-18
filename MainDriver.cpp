
#include <iostream>

#include "MapDriver.h"
#include "MapLoaderMain.h"
#include "PlayerDriver.h"
#include "CardsMain.h"
#include "BidingFacilityMain.h"



int main(){

    std::cout << "************************************************" << std::endl;
//    map::main();
    std::cout << "************************************************" << std::endl;

    std::cout << "************************************************" << std::endl;
    mapLoader::main();
    std::cout << "************************************************" << std::endl;

    std::cout << "************************************************" << std::endl;
    player::main();
    std::cout << "************************************************" << std::endl;

    std::cout << "************************************************" << std::endl;
    cards::main();
    std::cout << "************************************************" << std::endl;

    std::cout << "************************************************" << std::endl;
    biding::main();
    std::cout << "************************************************" << std::endl;

}


