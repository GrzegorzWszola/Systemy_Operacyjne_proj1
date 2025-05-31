
#include "Utilities.h"

Graph* GraphGeneration::createGraphFromFile(int **data) {
    int edges = data[0][0], nodes = data[0][1], startingNode = data[0][2], endingNode = data[0][3];
    Graph* graph = nullptr;
    //If the file structure is mst create non directed graph
    if (startingNode == -1 && endingNode == -1) {
        graph = new Graph(edges, nodes, startingNode, endingNode, false);
    } else {
        graph = new Graph(edges, nodes, startingNode, endingNode, true);
    }
    for (int i = 1; i <= edges; i++) {
        graph->addEdge(data[i][0], data[i][1], data[i][2]);
    }
    return graph;
}

Graph* GraphGeneration::createRandomGraph(int nodes, int density, int minCap, int maxCap, bool directed) {
    bool removeOnePercent = false;
    if (density == 99) {
        density = 100;
        removeOnePercent = true;
    }
    int maxEdges = 0;

    if (directed) maxEdges = nodes*(nodes-1);
    else maxEdges = nodes*(nodes-1)/2;

    int edges = (int)(density * maxEdges / 100.0);
    int edgeCounter = 0;

    bool** edgesList = new bool*[nodes];
    for (int i = 0; i < nodes; i++) {
        edgesList[i] = new bool[nodes]{false};
    }
    bool** inSpanningTree = new bool*[nodes];
    for (int i = 0; i < nodes; i++) {
        inSpanningTree[i] = new bool[nodes]{false};
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    Graph* graph = new Graph(edges, nodes, 0, 0, directed);

    for (int i = 0; i < nodes - 1; i++) {
        int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
        while (cap == 0) {
            cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
        }
        graph->addEdge(i, i + 1, cap);
        edgesList[i][i+1] = true;
        inSpanningTree[i][i+1] = true;
        edgeCounter++;
    }

    while (edgeCounter < edges) {
        int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
        int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
        int cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
        while (cap == 0) {
            cap = std::uniform_int_distribution<>(minCap, maxCap)(gen);
        }
        //Check for loops and exisitng edges
        if (randomNode == randomNextNode || edgesList[randomNode][randomNextNode]) continue;

        graph->addEdge(randomNode, randomNextNode, cap);
        //Adding edge to list
        edgesList[randomNode][randomNextNode] = true;
        edgeCounter++;
    }

    if (removeOnePercent) {
        int edgesToRemove = (int)(edges / 100.0);
        int j = 0;
        while (j < edgesToRemove) {
            int randomNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            int randomNextNode = std::uniform_int_distribution<>(0, nodes - 1)(gen);
            //Check if edge is not part of spanning tree to not delete important nodes
            if (inSpanningTree[randomNode][randomNextNode] || inSpanningTree[randomNextNode][randomNode]) continue;
            //Check to see if the edge exists within the graph
            if (!edgesList[randomNode][randomNextNode] || !edgesList[randomNextNode][randomNode]) continue;
            graph->removeEdge(randomNode, randomNextNode);
            edgesList[randomNode][randomNextNode] = false;
            j++;
        }
    }

    for (int i = 0; i < nodes - 1; i++) {
        delete[] inSpanningTree[i];
        delete[] edgesList[i];
    }
    delete[] edgesList;
    delete[] inSpanningTree;

    return graph;
}




