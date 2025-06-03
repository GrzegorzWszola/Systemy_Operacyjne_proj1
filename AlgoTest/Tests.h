#ifndef TESTS_H
#define TESTS_H

#include "../DataStructures/Graph.h"
#include "../Utilities/Utilities.h"
#include "../Algorithms/Algorithms.h"
#include "../GUI/GUI.h"

#define REPETITIONS 50

class Tests {
public:
    static void MSTTestsP(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed);
    static void MSTTestsK(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed);
    static void ShortestPathTestsD(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed);
    static void ShortestPathTestsBF(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed);
};

class GenerateResults {
public:
    static void generateResult();
};

#endif //TESTS_H
