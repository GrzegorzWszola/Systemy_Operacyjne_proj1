#include "Algorithms.h"

void ShortestPathAlgorithms::dijkstra(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    int nodes = graph->getNodes();
    bool* visited = new bool[nodes];
    int* distance = new int[nodes];
    int* previous = new int[nodes];

    auto start = std::chrono::high_resolution_clock::now();

    std::fill_n(distance, nodes, INF);
    std::fill_n(previous, nodes, -1);
    std::fill_n(visited, nodes, false);

    int source = graph->getStartingNode();
    distance[source] = 0;

    MinHeap minHeap(graph->getEdgeCounter());
    minHeap.insertElement(Edge(source, source, 0));

    //Iterating while heap is not empty
    while (!minHeap.empty()) {
        Edge current = minHeap.getMinElement();
        int u = current.to;

        //Checking if the node was already visited
        if (visited[u]) continue;
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
                minHeap.insertElement(Edge(u, v, distance[v]));
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


void ShortestPathAlgorithms::dijkstraList(Graph const *graph, std::chrono::milliseconds &timeList) {
    int nodes = graph->getNodes();
    bool* visited = new bool[nodes];
    int* distance = new int[nodes];
    int* previous = new int[nodes];

    std::fill_n(distance, nodes, INF);
    std::fill_n(previous, nodes, -1);
    std::fill_n(visited, nodes, false);
    distance[graph->getStartingNode()] = 0;

    MinHeap minHeap(graph->getEdgeCounter());
    minHeap.insertElement(Edge(graph->getStartingNode(), graph->getStartingNode(), 0));

    auto start = std::chrono::high_resolution_clock::now();

    while (!minHeap.empty()) {
        Edge current = minHeap.getMinElement();
        int u = current.to;

        if (visited[u])
            continue;

        visited[u] = true;

        const AdjList& adjList = graph->getAdjList(u);
        for (int v = 0; v < adjList.getSize(); v++) {
            Edge edge = adjList.getEdges()[v];
            if (edge.weight < 0) {
                std::cout << "Edge weight cannot be negative\n";
                return;
            }
            if (!visited[edge.to] && distance[u] != INF && distance[u] + edge.weight < distance[edge.to]) {
                distance[edge.to] = distance[u] + edge.weight;
                previous[edge.to] = u;
                minHeap.insertElement(Edge(u, edge.to, distance[edge.to]));
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printResultDistance(graph, nodes, distance);
    printResultPath(graph, nodes, distance, previous);

    delete[] visited;
    delete[] distance;
    delete[] previous;
}


void ShortestPathAlgorithms::bellmanFord(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    int* distance = new int[graph->getNodes()];
    int* previous = new int[graph->getNodes()];
    bool updated = false;
    //Setting up the table
    std::fill_n(distance, graph->getNodes(), INF);
    std::fill_n(previous, graph->getNodes(), -1);
    distance[graph->getStartingNode()] = 0;

    auto start = std::chrono::high_resolution_clock::now();
    //Iterating Vertex - 1 times to avoid negative loops
    for (int i = 0; i < graph->getNodes() - 1; i++) {
        updated = false;
        for (int u = 0; u < graph->getNodes(); u++) {
            for (int v = 0; v < graph->getNodes(); v++) {
                //Getting the weight of the edge to add
                int weight = graph->getAdjMatrix()[u][v];
                //Checking if the edge exists, if the path to the node is known and if the path is shorter
                if (weight != 0 && distance[u] != INF) {
                    int newDist = distance[u] + weight;
                    if (distance[v] > newDist) {
                        distance[v] = newDist;
                        previous[v] = u;
                        updated = true;
                    }
                }
            }
        }
        if (!updated) break;
    }

    //Checking for negative weight cycles after all iterations
    for (int u = 0; u < graph->getNodes(); u++) {
        for (int v = 0; v < graph->getNodes(); v++) {
            int weight = graph->getAdjMatrix()[u][v];
            if (weight != 0) {
                if (distance[u] != INF && distance[v] > distance[u] + weight) {
                    std::cout << "Negative weight cycle detected\n";
                    return;
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printResultDistance(graph, graph->getNodes(), distance);
    printResultPath(graph, graph->getNodes(), distance, previous);

    delete[] distance;
    delete[] previous;
}

void ShortestPathAlgorithms::bellmanFordList(Graph const *graph, std::chrono::milliseconds &timeList) {
    int* distance = new int[graph->getNodes()];
    int* previous = new int[graph->getNodes()];
    int n = graph->getNodes();
    bool updated = false;
    //Setting up the table
    std::fill_n(distance, graph->getNodes(), INF);
    std::fill_n(previous, graph->getNodes(), -1);
    distance[graph->getStartingNode()] = 0;

    auto start = std::chrono::high_resolution_clock::now();
    //Iterating Vertex - 1 times to avoid negative loops
    for (int i = 0; i < n - 1; i++) {
        updated = false;
        for (int u = 0; u < n; u++) {
            const AdjList &adjList = graph->getAdjList(u);
            for (int j = 0; j < adjList.getSize(); j++) {
                //Getting the weight of the edge to add
                int v = adjList.getEdges()[j].to;
                int weight = adjList.getEdges()[j].weight;
                //Checking if the edge exists, if the path to the node is known and if the path is shorter
                if (distance[u] != INF && weight != 0 && distance[v] > distance[u] + weight) {
                    distance[v] = distance[u] + weight;
                    previous[v] = u;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }

    //Checking for negative weight cycles after all iterations
    for (int u = 0; u < n; u++) {
        const AdjList &adjList = graph->getAdjList(u);
        for (int j = 0; j < adjList.getSize(); j++) {
            int v = adjList.getEdges()[j].to;
            int weight = adjList.getEdges()[j].weight;
            if (distance[u] != INF && distance[v] > distance[u] + weight) {
                std::cout << "Negative weight cycle detected\n";
                return;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printResultDistance(graph, graph->getNodes(), distance);
    printResultPath(graph, graph->getNodes(), distance, previous);

    delete[] distance;
    delete[] previous;
}


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