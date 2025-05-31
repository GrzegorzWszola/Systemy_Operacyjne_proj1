#include "Tests.h"

void Tests::MSTTestsP(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed) {
    auto timeMatrix = std::chrono::milliseconds{0};
    auto timeList = std::chrono::milliseconds{0};
    auto sumMatrix = std::chrono::milliseconds{0};
    auto sumList = std::chrono::milliseconds{0};
    for (int i = 0; i < REPETITIONS; i++) {
        const Graph* graph = GraphGeneration::createRandomGraph(nodes, denstity, minCap, maxCap, directed);

        MSTAlgorithms::prim(graph, timeMatrix);
        sumMatrix += timeMatrix;

        MSTAlgorithms::primList(graph, timeList);
        sumList += timeList;
        delete graph;
    }

    timeMatrixAvg = std::chrono::milliseconds(sumMatrix.count() / REPETITIONS);
    timeListAvg = std::chrono::milliseconds(sumList.count() / REPETITIONS);

}

void Tests::MSTTestsK(std::chrono::milliseconds &timeListAvg, std::chrono::milliseconds &timeMatrixAvg, int nodes, int denstity, int minCap, int maxCap, bool directed) {
    auto timeMatrix = std::chrono::milliseconds{0};
    auto timeList = std::chrono::milliseconds{0};
    auto sumMatrix = std::chrono::milliseconds{0};
    auto sumList = std::chrono::milliseconds{0};
    for (int i = 0; i < REPETITIONS; i++) {
        const Graph* graph = GraphGeneration::createRandomGraph(nodes, denstity, minCap, maxCap, directed);

        MSTAlgorithms::kruskal(graph, timeMatrix);
        sumMatrix += timeMatrix;

        MSTAlgorithms::kruskalList(graph, timeList);
        sumList += timeList;

        delete graph;
    }

    timeMatrixAvg = std::chrono::milliseconds(sumMatrix.count() / REPETITIONS);
    timeListAvg = std::chrono::milliseconds(sumList.count() / REPETITIONS);

}


