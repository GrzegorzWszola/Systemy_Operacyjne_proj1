#include "../DataStructures/Graph.h"
#include "../Utilities/Utilities.h"
#include "../Algorithms/Algorithms.h"
#include "Tests.h"

void testDjikstra(int nodes, int density, int minCap, int maxCap, bool directed, std::chrono::milliseconds &time, std::chrono::milliseconds &time2, int numThreads) {
    Graph* testGraph = GraphGeneration::createRandomGraph(nodes, density, minCap, maxCap, directed);
    // Testing normal Djikstra
    ShortestPathAlgorithms::dijkstra(testGraph, time);
    ShortestPathAlgorithms::djikstraMulti(testGraph, time2, numThreads);
}

void testDjikstraCorrectness(std::string filename) {
    int** graphData = FileHandler::readFile(filename);
    Graph* testGraph = GraphGeneration::createGraphFromFile(graphData);

    std::chrono::milliseconds time;
    std::chrono::milliseconds time2;

    // Testing normal Djikstra
    ShortestPathAlgorithms::dijkstraPrint(testGraph, time);
    ShortestPathAlgorithms::djikstraMultiPrint(testGraph, time2, 4);
}
