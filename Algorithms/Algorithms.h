#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#define INF INT_MAX

#include "../DataStructures//MinHeapDist.h"
#include <chrono>
#include <climits>

#include "../DataStructures/Graph.h"
#include "../DataStructures/MinHeap.h"
#include "../DataStructures/DisjointSet.h"
#include "../DataStructures/Stack.h"

class ShortestPathAlgorithms {
public:
    static void printResultDistance(Graph const *&graph, int nodes, int* &distance);
    static void printResultPath(Graph const *&graph, int nodes, int* &distance, int* &previous);
    static void printPath(int node, int* &previous);
    static void dijkstra(Graph const *graph, std::chrono::milliseconds &timeList);
    static void dijkstraPrint(Graph const *graph, std::chrono::milliseconds &timeList);
    static void djikstraMulti(Graph const *graph, std::chrono::milliseconds &timeList, int numThreads);
    static void djikstraMultiPrint(Graph const *graph, std::chrono::milliseconds &timeList, int numThreads);
};


#endif //ALGORITHMS_H
