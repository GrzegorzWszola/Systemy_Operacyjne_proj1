#include "../DataStructures/Graph.h"
#include "../Utilities/Utilities.h"
#include "../Algorithms/Algorithms.h"

void testDjikstra() {
    int nodes = 1000;
    int density = 60;
    int minCap = 10;
    int maxCap = 100;
    bool directed = false;
    Graph* testGraph = GraphGeneration::createRandomGraph(nodes, density, minCap, maxCap, directed);

    std::chrono::milliseconds time;

    // Testing normal Djikstra
    ShortestPathAlgorithms::dijkstra(testGraph, time);

    std::cout << "Time for djikstra normal: " << time.count() << std::endl;
}

void testDjikstraCorrectness() {
    std::string filename = "/home/grzegorz/Desktop/systemy_op/AIZO-project-2/dane_do_testu_poprawnosci.txt";
    int** graphData = FileHandler::readFile(filename);
    Graph* testGraph = GraphGeneration::createGraphFromFile(graphData);

    std::chrono::milliseconds time;

    // Testing normal Djikstra
    ShortestPathAlgorithms::dijkstraPrint(testGraph, time);

    std::cout << "Time for djikstra normal: " << time.count() << std::endl;
}