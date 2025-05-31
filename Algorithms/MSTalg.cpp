
#include "Algorithms.h"
void MSTAlgorithms::prim(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    auto start = std::chrono::high_resolution_clock::now();
    // Liczba wierzchołków w grafie
    int n = graph->getNodes();

    // Pobranie macierzy sąsiedztwa (dla tych samych danych)
    int** adjMatrix = graph->getAdjMatrix();

    // Tablica, aby śledzić odwiedzone wierzchołki
    bool* inMST = new bool[n];
    for (int i = 0; i < n; ++i) {
        inMST[i] = false; // Na początku żaden wierzchołek nie jest w MST
    }

    // Tablica rodziców dla rekonstrukcji MST
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = -1; // Na początku każdy wierzchołek ma `-1` jako rodzica
    }

    // Tablica najmniejszego kosztu dojścia do każdego wierzchołka
    int* key = new int[n];
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX; // Na początku wszystkie koszty przejścia są "nieskończone"
    }
    key[0] = 0; // Startujemy od wierzchołka `0`, koszt przejścia do niego wynosi `0`

    int edges = graph->getEdgeCounter(); // Liczba krawędzi
    MinHeap heap(edges);

    Edge* resultEdges = new Edge[n - 1]; // Wynikowa tablica krawędzi MST
    int edgeCount = 0;                   // Aktualna liczba dodanych krawędzi
    int totalWeight = 0;                 // Suma wag krawędzi wchodzących do MST

    // Dodanie pierwszego wierzchołka do kopca (z wagą 0, żeby zacząć od wierzchołka 0)
    Edge startEdge(0, 0, 0); // Wierzchołek 0, waga 0
    heap.insertElement(startEdge);

    // Algorytm Prima
    while (!heap.empty()) {
        // Pobranie najmniejszej krawędzi z kopca
        Edge currentEdge = heap.getMinElement();
        int u = currentEdge.to; // Wierzchołek docelowy krawędzi `u`

        // Jeżeli wierzchołek jest już w MST, pomijamy go
        if (inMST[u]) continue;

        // Oznacz wierzchołek jako dołączony do MST
        inMST[u] = true;

        // Dodaj krawędź do MST, jeśli jej rodzic istnieje
        if (parent[u] != -1) {
            resultEdges[edgeCount++] = Edge(parent[u], u, currentEdge.weight);
            totalWeight += currentEdge.weight; // Zwiększenie sumarycznej wagi MST
        }

        // Przeglądanie wszystkich sąsiadów wierzchołka `u`
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] != 0 && !inMST[v]) {
                // Sprawdź, czy bieżąca krawędź ma mniejszą wagę
                if (adjMatrix[u][v] < key[v]) {
                    // Zaktualizuj klucz wierzchołka `v` (najmniejszy koszt dojścia)
                    key[v] = adjMatrix[u][v];

                    // Dodaj krawędź do kopca
                    Edge newEdge(u, v, adjMatrix[u][v]);
                    heap.insertElement(newEdge);

                    // Zaktualizuj rodzica wierzchołka `v`
                    parent[v] = u;
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printResult(graph, resultEdges, edgeCount, totalWeight);

    // Sprzątanie (usuwanie tablic dynamicznych)
    delete[] inMST;
    delete[] parent;
    delete[] resultEdges;
    delete[] key;
}

void MSTAlgorithms::primList(Graph const *graph, std::chrono::milliseconds &timeList) {
    auto start = std::chrono::high_resolution_clock::now();
    // Liczba wierzchołków w grafie
    int n = graph->getNodes();

    // Tablica, aby śledzić odwiedzone wierzchołki
    bool* inMST = new bool[n];
    for (int i = 0; i < n; ++i) {
        inMST[i] = false; // Na początku żaden wierzchołek nie jest w MST
    }

    // Tablica rodziców dla rekonstrukcji MST
    int* parent = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = -1; // Na początku każdy wierzchołek ma `-1` jako rodzica
    }

    // Tablica najmniejszego kosztu dojścia do każdego wierzchołka
    int* key = new int[n];
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX; // Na początku wszystkie koszty przejścia są "nieskończone"
    }
    key[0] = 0; // Startujemy od wierzchołka `0`, koszt przejścia do niego wynosi `0`

    // Licznik krawędzi i suma wag
    Edge* resultEdges = new Edge[n - 1]; // Wynikowa tablica krawędzi MST
    int edgeCount = 0;                   // Aktualna liczba dodanych krawędzi
    int totalWeight = 0;                 // Suma wag krawędzi wchodzących do MST

    // Kopiec priorytetowy na krawędzie
    MinHeap heap(graph->getEdgeCounter());

    // Dodanie pierwszego wierzchołka do kopca (z wagą 0, żeby zacząć od wierzchołka 0)
    Edge startEdge(0, 0, 0); // Wierzchołek początkowy, waga 0
    heap.insertElement(startEdge);

    // Algorytm Prima
    while (!heap.empty()) {
        // Pobranie najmniejszej krawędzi z kopca
        Edge currentEdge = heap.getMinElement();
        int u = currentEdge.to; // Wierzchołek docelowy krawędzi `u`

        // Jeżeli wierzchołek jest już w MST, pomijamy go
        if (inMST[u]) continue;

        // Oznacz wierzchołek jako dołączony do MST
        inMST[u] = true;

        // Dodaj krawędź do MST, jeśli jej rodzic istnieje
        if (parent[u] != -1) {
            resultEdges[edgeCount++] = Edge(parent[u], u, currentEdge.weight);
            totalWeight += currentEdge.weight; // Zwiększenie sumarycznej wagi MST
        }

        // Przeglądanie wszystkich sąsiadów wierzchołka `u` z listy sąsiedztwa
        const AdjList& adjList = graph->getAdjList(u);
        for (int v = 0; v < adjList.getSize(); v++) {
            Edge nextNode = adjList.getEdges()[v];
            if (nextNode.weight < key[nextNode.to]) {
                key[nextNode.to] = nextNode.weight;
                Edge newEdge(u, nextNode.to, nextNode.weight);
                heap.insertElement(newEdge);
                parent[nextNode.to] = u;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printResult(graph, resultEdges, edgeCount, totalWeight);

    // Sprzątanie pamięci
    delete[] inMST; inMST = nullptr;
    delete[] parent; parent = nullptr;
    delete[] key; key = nullptr;
    delete[] resultEdges; resultEdges = nullptr;
}

void MSTAlgorithms::kruskal(Graph const *graph, std::chrono::milliseconds &timeMatrix) {
    int n = graph->getNodes();
    auto mstSet = new Edge*[n - 1];
    auto visited = new bool[n];
    MinHeap edgeHeap(graph->getEdgeCounter());
    int sum = 0;
    int setCounter = 0;
    std::fill_n(visited, graph->getNodes(), false);

    Edge* mstSetResult = new Edge[n - 1];

    auto start = std::chrono::high_resolution_clock::now();
    //Adding all edges into the list and sorting them at the same time)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int weight = graph->getAdjMatrix()[i][j];
            if (weight != 0) {
                edgeHeap.insertElement(Edge(i, j, weight));
            }
        }
    }

    //Creating disjoint set with max of n nodes
    DisjointSet dsSet(n);

    int edgeCount = 0;                   // Aktualna liczba dodanych krawędzi
    int totalWeight = 0;

    //Iterating through all edges in the sorted edges
    while (!edgeHeap.empty()){
        Edge smallestEdge = edgeHeap.getMinElement();
        int u = smallestEdge.from;
        int v = smallestEdge.to;
        int weight = smallestEdge.weight;

        //Checking if they are in the same set if not unionising
        if (dsSet.find(u) != dsSet.find(v)) {
            sum += weight;
            mstSetResult[setCounter++] = Edge(u, v, weight);
            dsSet.unionBySize(u, v);
            edgeCount++;
            totalWeight += weight;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    timeMatrix = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printResult(graph, mstSetResult, edgeCount, totalWeight);

    delete[] mstSetResult; mstSetResult = nullptr;
    delete[] visited; visited = nullptr;
    delete[] mstSet; mstSet = nullptr;
}

void MSTAlgorithms::kruskalList(Graph const *graph, std::chrono::milliseconds &timeList) {
    int n = graph->getNodes();
    auto mstSet = new Edge*[n - 1];
    auto visited = new bool[n];
    MinHeap edgeHeap(graph->getEdgeCounter());
    int sum = 0;
    int setCounter = 0;
    std::fill_n(visited, graph->getNodes(), false);

    Edge* mstSetResult = new Edge[n - 1];


    auto start = std::chrono::high_resolution_clock::now();
    //Adding all edges into the list and sorting them at the same time
    for (int i = 0; i < n; i++) {
        const AdjList &adjList = graph->getAdjList(i);
        // Cache edges locally
        const auto *edges = adjList.getEdges();
        int size = adjList.getSize();
        int count = 0;
        Edge* tempArr = new Edge[size];
        for (int j = 0; j < size; j++) {
            const Edge &edge = edges[j];
            if (i < edge.to) {
                tempArr[count++] = edge;
            }
        }
        if (count > 0) {
            edgeHeap.bulkInsert(tempArr, count);
        }
        delete[] tempArr;
    }


    //Creating disjoint set with max of n nodes
    DisjointSet dsSet(n);

    int edgeCount = 0;
    int totalWeight = 0;

    //Iterating through all edges in the sorted edges
    while (!edgeHeap.empty()){
        Edge smallestEdge = edgeHeap.getMinElement();
        int u = smallestEdge.from;
        int v = smallestEdge.to;
        int weight = smallestEdge.weight;

        //Checking if they are in the same set if not unionising
        if (dsSet.find(u) != dsSet.find(v)) {
            sum += weight;
            mstSetResult[setCounter++] = Edge(u, v, weight);
            dsSet.unionBySize(u, v);
            edgeCount++;
            totalWeight += weight;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printResult(graph, mstSetResult, edgeCount, totalWeight);

    delete[] mstSetResult; mstSetResult = nullptr;
    delete[] visited; visited = nullptr;
    delete[] mstSet; mstSet = nullptr;
}


void MSTAlgorithms::printResult(Graph const *graph, Edge* resultEdges, int edgeCount, int totalWeight) {
    std::cout << "Minimal Spanning Tree Edges (u - v) with weights:\n";
    for (int i = 0; i < edgeCount; ++i) {
        std::cout << resultEdges[i].from << " - " << resultEdges[i].to
                  << " : " << resultEdges[i].weight << "\n";
    }
    std::cout << "Total weight of MST: " << totalWeight << "\n";
    std::cout << "\n\n";
}




