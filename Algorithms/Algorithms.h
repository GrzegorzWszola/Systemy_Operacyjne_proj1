#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#define INF INT_MAX

#include <chrono>
#include <climits>

#include "../DataStructures/Graph.h"
#include "../DataStructures/MinHeap.h"
#include "../DataStructures/DisjointSet.h"
#include "../DataStructures/Stack.h"

enum class Color { WHITE, GRAY, BLACK };

class MSTAlgorithms {
    static void printResult(Graph const *graph, Edge* resultEdges, int edgeCount, int totalWeight);
public:
    static void prim(Graph const *graph, std::chrono::milliseconds &timeMatrix);
    static void primList(Graph const *graph, std::chrono::milliseconds &timeList);
    static void kruskal(Graph const *graph, std::chrono::milliseconds &timeMatrix);
    static void kruskalList(Graph const *graph, std::chrono::milliseconds &timeList);
};

class ShortestPathAlgorithms {
    static void printResultDistance(Graph const *&graph, int nodes, int* &distance);
    static void printResultPath(Graph const *&graph, int nodes, int* &distance, int* &previous);
    static void printPath(int node, int* &previous);
public:
    static void dijkstra(Graph const *graph, std::chrono::milliseconds &timeMatrix);
    static void dijkstraList(Graph const *graph, std::chrono::milliseconds &timeList);
    static void bellmanFord(Graph const *graph, std::chrono::milliseconds &timeMatrix);
    static void bellmanFordList(Graph const *graph, std::chrono::milliseconds &timeList);
};


#endif //ALGORITHMS_H
