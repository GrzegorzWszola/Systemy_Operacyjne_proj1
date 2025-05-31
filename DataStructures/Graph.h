#ifndef GRAPHS_H
#define GRAPHS_H

#include <iostream>
#include <stdexcept>

struct Edge {
    int from;
    int to;
    int weight;
    explicit Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
};

class AdjList {
    Edge* edges;
    int size;
    int capacity;

public:
    AdjList() : edges(nullptr), size(0), capacity(1) {edges = new Edge[capacity];}
    ~AdjList() {delete[] edges;}

    void resize() {
        capacity *= 2;
        Edge* newEdges = new Edge[capacity];
        for (int i = 0; i < size; ++i) {
            newEdges[i] = edges[i];
        }
        delete[] edges;
        edges = newEdges;
    }

    void addEdge(int from, int to, int weight) {
        if (size == capacity) {
            resize();
        }
        edges[size++] = Edge(from, to, weight);
    }

    bool removeEdge(int to) {
        for (int i = 0; i < size; ++i) {
            if (edges[i].to == to) {
                // Przesuwamy elementy, aby usunąć lukę
                for (int j = i; j < size - 1; ++j) {
                    edges[j] = edges[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }
    Edge* getEdges() const {return edges;}
    int getSize() const {return size;}
};


class Graph {
    AdjList* adjList;
    int** adjMatrix;
    int nodes;
    int edgeCounter;
    int startingNode;
    int endingNode;
    bool directed;

public:
    Graph(int numberEdges, int numberNodes, int sNode, int eNode, bool directedI)
        : nodes(numberNodes), edgeCounter(numberEdges), startingNode(sNode), endingNode(eNode), directed(directedI) {
        // Alokujemy listę sąsiedztwa
        adjList = new AdjList[nodes];

        // Alokujemy jednowymiarową macierz sąsiedztwa
        adjMatrix = new int*[nodes];
        for (int i = 0; i < nodes; ++i) {
            adjMatrix[i] = new int[nodes];
            for (int j = 0; j < nodes; ++j) {
                adjMatrix[i][j] = 0;
            }
        }

    }

    ~Graph() {
        delete[] adjList;
        for (int i = 0; i < nodes; ++i) {
            delete[] adjMatrix[i];
        }
        delete[] adjMatrix;
    }

    void addEdge(int source, int destination, int capacity) {
        adjList[source].addEdge(source, destination, capacity);
        adjMatrix[source][destination] = capacity;
        if (!directed) {
            adjList[destination].addEdge(destination, source, capacity);
            adjMatrix[destination][source] = capacity;
        }
        edgeCounter++;
    }


    void removeEdge(int source, int destination) {
        if (adjList[source].removeEdge(destination)) {
            adjMatrix[source][destination] = 0;
            if (!directed) {
                adjList[destination].removeEdge(source);
                adjMatrix[destination][source] = 0;
            }
            edgeCounter--;
        }
    }


    void setStartingNode(int value) {startingNode = value;}
    void setEndingNode(int value) {endingNode = value;}
    int getStartingNode() const {return startingNode;}
    int getEndingNode() const {return endingNode;}
    int getNodes() const {return nodes;}
    int getEdgeCounter() const {return edgeCounter;}
    bool isDirected() const {return directed;}
    int** getAdjMatrix() const {return adjMatrix;}
    const int* getAdjMatrixRow(int node) const {
        if (node < 0 || node >= nodes) {
            throw std::out_of_range("Node index out of range");
        }
        return adjMatrix[node];
    }
    const AdjList& getAdjList(int node) const {
        if (node < 0 || node >= nodes) {
            throw std::out_of_range("Node index out of range");
        }
        return adjList[node];
    }

    void printMatrix() const {
        std::cout << "Adjacency Matrix:\n";
        printf("    ");
        for (int j = 0; j < nodes; ++j) {
            printf("%4d", j);
        }
        printf("\n");
        printf("   ");
        for (int j = 0; j < nodes; ++j) {
            printf("----");
        }
        printf("\n");
        for (int i = 0; i < nodes; ++i) {
            printf("%2d |", i);
            for (int j = 0; j < nodes; ++j) {
                printf("%4d", adjMatrix[i][j]);
            }
            printf("\n");
        }
    }

    void printList() const {
        for (int i = 0; i < nodes; ++i) {
            std::cout << i << ":";
            for (int j = 0; j < adjList[i].getSize(); ++j) {
                Edge e = adjList[i].getEdges()[j];
                std::cout << " -> (" << e.to << ": " << e.weight << ")";
            }
            std::cout << "\n";
        }
    }
};


#endif

