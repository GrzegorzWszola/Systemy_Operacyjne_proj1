// reference for the function
// int nodes, int density, int minCap, int maxCap, bool directed

#include "Tests.h"
#include <chrono>
#include <iostream>

int minCap = 0;
int maxCap = 10;
bool directed = false;
int repeats = 1;
int numThreads = 4;

// Sparse graphs not many nodes
void TS_1(int nodes, int density) {
    int timeAvg = 0, timeMAvg = 0;
    std::chrono::milliseconds timeSum{0}, timeMSum{0}, time{0}, timeM{0};\
    for (int i = 0; i < repeats; ++i){
        testDjikstra(nodes, density, minCap, maxCap, directed, time, timeM, numThreads);
        timeSum += time; 
        timeMSum += timeM;
    }
    timeAvg = timeSum.count()/repeats;
    timeMAvg = timeMSum.count()/repeats;
    std::cout << timeAvg << ", " << timeMAvg;  
}

void TS_2(int nodes, int density) {
    int timeAvg = 0, timeMAvg = 0;
    std::chrono::milliseconds timeSum{0}, timeMSum{0}, time{0}, timeM{0};\
    for (int i = 0; i < repeats; ++i){
        testDjikstra(nodes, density, minCap, maxCap, directed, time, timeM, numThreads);
        timeSum += time; 
        timeMSum += timeM;
    }
    timeAvg = timeSum.count()/repeats;
    timeMAvg = timeMSum.count()/repeats;
    std::cout << ", " << timeAvg << ", " << timeMAvg;  
}

void TS_3(int nodes, int density) {
    int timeAvg = 0, timeMAvg = 0;
    std::chrono::milliseconds timeSum{0}, timeMSum{0}, time{0}, timeM{0};\
    for (int i = 0; i < repeats; ++i){
        testDjikstra(nodes, density, minCap, maxCap, directed, time, timeM, numThreads);
        timeSum += time; 
        timeMSum += timeM;
    }
    timeAvg = timeSum.count()/repeats;
    timeMAvg = timeMSum.count()/repeats;
    std::cout << ", " << timeAvg << ", " << timeMAvg;  
}



void testScenarios() {
    int nodes1 = 100, nodes2 = 500, nodes3 = 1500, nodes4 = 3000, nodes5 = 5000;
    std::cout << "#nodes 100, 500, 1500, 3000, 5000" << std::endl;
    std::cout << "#[normal, multithread, ...]" << std::endl;
    std::cout << "25_density = [";
    int density = 25;
    TS_1(nodes1, density); TS_2(nodes2, density); TS_2(nodes3, density); TS_2(nodes4, density); TS_3(nodes5, density);
    std::cout << "]\n";

    std::cout << "50_density = [";
    density = 50;
    TS_1(nodes1, density); TS_2(nodes2, density); TS_2(nodes3, density); TS_2(nodes4, density); TS_3(nodes5, density);
    std::cout << "]\n";

    std::cout << "75_density = [";
    density = 75;
    TS_1(nodes1, density); TS_2(nodes2, density); TS_2(nodes3, density); TS_2(nodes4, density); TS_3(nodes5, density);
    std::cout << "]\n";

    std::cout << "99_density = [";
    density = 99;
    TS_1(nodes1, density); TS_2(nodes2, density); TS_2(nodes3, density); TS_2(nodes4, density); TS_3(nodes5, density);
    std::cout << "]\n";
}