#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include "../DataStructures/Graph.h"

class FileHandler {
public:
    static int** readFile(std::string fileName);
};

class GraphGeneration {
public:
    static Graph* createGraphFromFile(int** data);
    static Graph* createRandomGraph(int nodes, int density, int minCap, int maxCap, bool directed);
};

#endif
