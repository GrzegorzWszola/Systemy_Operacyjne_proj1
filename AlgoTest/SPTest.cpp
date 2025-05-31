#include "Tests.h"

void Tests::ShortestPathTestsD(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed) {
    auto timeMatrix = std::chrono::milliseconds{0};
    auto timeList = std::chrono::milliseconds{0};
    auto sumMatrix = std::chrono::milliseconds{0};
    auto sumList = std::chrono::milliseconds{0};
    for (int i = 0; i < REPETITIONS; i++) {
        const Graph* graph = GraphGeneration::createRandomGraph(nodes, denstity, minCap, maxCap, directed);

        ShortestPathAlgorithms::dijkstra(graph, timeMatrix);
        sumMatrix += timeMatrix;

        ShortestPathAlgorithms::dijkstraList(graph, timeList);
        sumList += timeList;

        delete graph;
    }

    timeMatrixAvg = std::chrono::milliseconds(sumMatrix.count() / REPETITIONS);
    timeListAvg = std::chrono::milliseconds(sumList.count() / REPETITIONS);
}

void Tests::ShortestPathTestsBF(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed) {
    auto timeMatrix = std::chrono::milliseconds{0};
    auto timeList = std::chrono::milliseconds{0};
    auto sumMatrix = std::chrono::milliseconds{0};
    auto sumList = std::chrono::milliseconds{0};
    for (int i = 0; i < REPETITIONS; i++) {
        const Graph* graph = GraphGeneration::createRandomGraph(nodes, denstity, minCap, maxCap, directed);

        ShortestPathAlgorithms::bellmanFord(graph, timeMatrix);
        sumMatrix += timeMatrix;

        ShortestPathAlgorithms::bellmanFordList(graph, timeList);
        sumList += timeList;

        delete graph;
    }

    timeMatrixAvg = std::chrono::milliseconds(sumMatrix.count() / REPETITIONS);
    timeListAvg = std::chrono::milliseconds(sumList.count() / REPETITIONS);

}
