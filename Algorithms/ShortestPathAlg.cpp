#include "Algorithms.h"
#include "../DataStructures/MinHeapDist.h"


void ShortestPathAlgorithms::dijkstra(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    int nodes = graph->getNodes();
    bool* visited = new bool[nodes];
    int* distance = new int[nodes];
    int* previous = new int[nodes];

    std::fill_n(distance, nodes, INF);
    std::fill_n(previous, nodes, -1);
    std::fill_n(visited, nodes, false);

    int source = graph->getStartingNode();
    distance[source] = 0;

    MinHeapDist minHeap(graph->getEdgeCounter());
    minHeap.insertElement(source, 0);

    auto start = std::chrono::high_resolution_clock::now();

    while (!minHeap.empty()) {
        HeapNode current = minHeap.getMinElement();
        int u = current.vertex;

        if (visited[u])
            continue;

        visited[u] = true;

        for (int v = 0; v < nodes; v++) {
            int weight = graph->getAdjMatrix()[u][v];
            if (weight < 0) {
                std::cout << "Edge weight cannot be negative\n";
                return;
            }
            if (weight > 0 && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                minHeap.insertElement(v, distance[v]);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    delete[] visited;
    delete[] distance;
    delete[] previous;
}

void ShortestPathAlgorithms::dijkstraPrint(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    int nodes = graph->getNodes();
    bool* visited = new bool[nodes];
    int* distance = new int[nodes];
    int* previous = new int[nodes];

    std::fill_n(distance, nodes, INF);
    std::fill_n(previous, nodes, -1);
    std::fill_n(visited, nodes, false);

    int source = graph->getStartingNode();
    distance[source] = 0;

    MinHeapDist minHeap(graph->getEdgeCounter());
    minHeap.insertElement(source, 0);

    auto start = std::chrono::high_resolution_clock::now();

    while (!minHeap.empty()) {
        HeapNode current = minHeap.getMinElement();
        int u = current.vertex;

        if (visited[u])
            continue;

        visited[u] = true;

        for (int v = 0; v < nodes; v++) {
            int weight = graph->getAdjMatrix()[u][v];
            if (weight < 0) {
                std::cout << "Edge weight cannot be negative\n";
                return;
            }
            if (weight > 0 && distance[u] != INF && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                minHeap.insertElement(v, distance[v]);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printResultDistance(graph, nodes, distance);
    printResultPath(graph, nodes, distance, previous);

    delete[] visited;
    delete[] distance;
    delete[] previous;
}

// void ShortestPathAlgorithms::dijkstraList(Graph const *graph, std::chrono::milliseconds &timeList) {
//     int nodes = graph->getNodes();
//     bool* visited = new bool[nodes];
//     int* distance = new int[nodes];
//     int* previous = new int[nodes];

//     std::fill_n(distance, nodes, INF);
//     std::fill_n(previous, nodes, -1);
//     std::fill_n(visited, nodes, false);

//     int source = graph->getStartingNode();
//     distance[source] = 0;

//     MinHeapDist minHeap(graph->getEdgeCounter());
//     minHeap.insertElement(source, 0);

//     auto start = std::chrono::high_resolution_clock::now();

//     while (!minHeap.empty()) {
//         HeapNode current = minHeap.getMinElement();
//         int u = current.vertex;

//         if (visited[u])
//             continue;

//         visited[u] = true;

//         const AdjList& adjList = graph->getAdjList(u);
//         for (int v = 0; v < adjList.getSize(); v++) {
//             Edge edge = adjList.getEdges()[v];
//             if (edge.weight < 0) {
//                 std::cout << "Edge weight cannot be negative\n";
//                 return;
//             }
//             if (!visited[edge.to] && distance[u] != INF && distance[u] + edge.weight < distance[edge.to]) {
//                 distance[edge.to] = distance[u] + edge.weight;
//                 previous[edge.to] = u;
//                 minHeap.insertElement(edge.to, distance[edge.to]);
//             }
//         }
//     }

//     auto end = std::chrono::high_resolution_clock::now();
//     timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

//     printResultDistance(graph, nodes, distance);
//     printResultPath(graph, nodes, distance, previous);

//     delete[] visited;
//     delete[] distance;
//     delete[] previous;
// }

void ShortestPathAlgorithms::printResultDistance(Graph const *&graph, int nodes, int* &distance) {
    std::cout << "Odleglosc od: " << graph->getStartingNode() << ", do kolejnych sasiadow: " << std::endl;
    for (int i = 0; i < nodes; i++) {
        std::cout << i << ": ";
        if (distance[i] == INF)
            std::cout << "unreachable\n";
        else
            std::cout << distance[i] << "\n";
    }
}

void ShortestPathAlgorithms::printResultPath(Graph const *&graph, int nodes, int* &distance, int* &previous) {
    std::cout << "Sciezka od: " << graph->getStartingNode() << ", do kolejnych wierzcholkow" << std::endl;
    for (int i = 0; i < nodes; i++) {
        std::cout << i << ": ";
        if (distance[i] == INF) {
            std::cout << "unreachable\n";
        } else {
            printPath(i, previous);
            std::cout << "\n";
        }
    }
}

void ShortestPathAlgorithms::printPath(int node, int* &previous) {
    if (previous[node] == -1) {
        std::cout << node;
        return;
    }
    printPath(previous[node], previous);
    std::cout << " -> " << node;
}