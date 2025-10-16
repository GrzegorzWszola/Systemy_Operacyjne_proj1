#include "Algorithms.h"
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>

void ShortestPathAlgorithms::djikstraMulti(Graph const *graph, 
                                           std::chrono::milliseconds &timeList, 
                                           int numThreads) {
    int nodes = graph->getNodes();
    std::atomic<int>* distance = new std::atomic<int>[nodes];
    int* previous = new int[nodes];

    for (int i = 0; i < nodes; i++) {
        distance[i].store(INF);
        previous[i] = -1;
    }

    int source = graph->getStartingNode();
    distance[source].store(0);

    MinHeapDist minHeap(graph->getEdgeCounter());
    minHeap.insertElement(source, 0);

    std::mutex heapMutex;
    std::mutex previousMutex;
    std::condition_variable cv;
    
    std::atomic<int> workingThreads(0);
    std::atomic<int> waitingThreads(0);
    std::atomic<bool> finished(false);

    auto start = std::chrono::high_resolution_clock::now();

    auto worker = [&]() {
        while (true) {
            HeapNode current;
            bool gotElement = false;
            
            {
                std::unique_lock<std::mutex> lock(heapMutex);
                
                // Sprawdź czy koniec zanim czekamy
                if (finished.load()) {
                    return;
                }
                
                // Czekaj na element
                while (minHeap.empty() && !finished.load()) {
                    waitingThreads++;  // Sygnalizuj że czekam
                    
                    // Sprawdź warunek zakończenia
                    if (minHeap.empty() && workingThreads.load() == 0) {
                        finished.store(true);
                        cv.notify_all();
                        return;
                    }
                    
                    waitingThreads--;
                    cv.wait(lock);
                }
                
                if (finished.load()) {
                    return;
                }
                
                if (!minHeap.empty()) {
                    current = minHeap.getMinElement();
                    gotElement = true;
                    workingThreads++;  // Zaczynam pracę
                }
            }
            
            if (!gotElement) continue;
            
            int u = current.vertex;
            int currentDist = current.distance;
            
            // Sprawdź czy to przestarzały wpis
            if (currentDist > distance[u].load()) {
                workingThreads--;
                continue;
            }
            
            // Relaksacja krawędzi (bez mutexa!)
            const AdjList& adjList = graph->getAdjList(u);
            for (int v = 0; v < adjList.getSize(); v++) {
                Edge edge = adjList.getEdges()[v];
                
                if (edge.weight < 0) {
                    std::cout << "Edge weight cannot be negative\n";
                    finished.store(true);
                    workingThreads--;
                    cv.notify_all();
                    return;
                }
                
                int u_dist = distance[u].load();
                if (u_dist == INF) continue;
                
                int newDist = u_dist + edge.weight;
                int oldDist = distance[edge.to].load();
                
                // Atomowa aktualizacja bez mutexa
                while (newDist < oldDist) {
                    if (distance[edge.to].compare_exchange_strong(oldDist, newDist)) {
                        // Zaktualizowanie powiodło się
                        {
                            std::lock_guard<std::mutex> lock(previousMutex);
                            previous[edge.to] = u;
                        }
                        
                        // Dodaj do kopca i obudź inny wątek
                        {
                            std::lock_guard<std::mutex> lock(heapMutex);
                            minHeap.insertElement(edge.to, newDist);
                            cv.notify_one();
                        }
                        break;
                    }
                    // compare_exchange_strong zaktualizuje oldDist jeśli się nie powiedzie
                }
            }
            
            workingThreads--;  // Koniec pracy
            
            // Obudź inne wątki by mogły sprawdzić warunek zakończenia
            {
                std::lock_guard<std::mutex> lock(heapMutex);
                cv.notify_all();
            }
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(worker);
    }
    
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    delete[] distance;
    delete[] previous;
}

void ShortestPathAlgorithms::djikstraMultiPrint(Graph const *graph, std::chrono::milliseconds &timeList, int numThreads) {
    int nodes = graph->getNodes();
    bool* visited = new bool[nodes];
    std::atomic<int>* distance = new std::atomic<int>[nodes];
    int* previous = new int[nodes];

    for (int i = 0; i < nodes; i++) {
        distance[i].store(INF);
    }
    std::fill_n(previous, nodes, -1);
    std::fill_n(visited, nodes, false);

    int source = graph->getStartingNode();
    distance[source].store(0);

    MinHeapDist minHeap(graph->getEdgeCounter());
    minHeap.insertElement(source, 0);

    std::mutex heapMutex;
    std::mutex previousMutex; 
    std::condition_variable cv;

    std::atomic<int> workingThreads(0);
    std::atomic<int> waitingThreads(0);
    std::atomic<bool> finished(false);

    auto start = std::chrono::high_resolution_clock::now();

    auto worker = [&]() {
        while (true) {
            HeapNode current;
            bool gotElement = false;
            
            {
                std::unique_lock<std::mutex> lock(heapMutex);
                
                //  Sprawdź czy koniec zanim czekamy
                if (finished.load()) {
                    return;
                }
                
                // Czekaj na element
                while (minHeap.empty() && !finished.load()) {
                    waitingThreads++;  // Sygnalizuj że czekam
                    
                    // Sprawdź warunek zakończenia
                    if (minHeap.empty() && workingThreads.load() == 0) {
                        finished.store(true);
                        cv.notify_all();
                        return;
                    }
                    
                    waitingThreads--;
                    cv.wait(lock);
                }
                
                if (finished.load()) {
                    return;
                }
                
                if (!minHeap.empty()) {
                    current = minHeap.getMinElement();
                    gotElement = true;
                    workingThreads++;  // Zaczynam pracę
                }
            }
            
            if (!gotElement) continue;
            
            int u = current.vertex;
            int currentDist = current.distance;
            
            // Sprawdź czy to przestarzały wpis
            if (currentDist > distance[u].load()) {
                workingThreads--;
                continue;
            }
            
            // Relaksacja krawędzi (bez mutexa!)
            const AdjList& adjList = graph->getAdjList(u);
            for (int v = 0; v < adjList.getSize(); v++) {
                Edge edge = adjList.getEdges()[v];
                
                if (edge.weight < 0) {
                    std::cout << "Edge weight cannot be negative\n";
                    finished.store(true);
                    workingThreads--;
                    cv.notify_all();
                    return;
                }
                
                int u_dist = distance[u].load();
                if (u_dist == INF) continue;
                
                int newDist = u_dist + edge.weight;
                int oldDist = distance[edge.to].load();
                
                // Atomowa aktualizacja bez mutexa
                while (newDist < oldDist) {
                    if (distance[edge.to].compare_exchange_strong(oldDist, newDist)) {
                        // Zaktualizowanie powiodło się
                        {
                            std::lock_guard<std::mutex> lock(previousMutex);
                            previous[edge.to] = u;
                        }
                        
                        // Dodaj do kopca i obudź inny wątek
                        {
                            std::lock_guard<std::mutex> lock(heapMutex);
                            minHeap.insertElement(edge.to, newDist);
                            cv.notify_one();
                        }
                        break;
                    }
                    // compare_exchange_strong zaktualizuje oldDist jeśli się nie powiedzie
                }
            }
            
            workingThreads--;  // Koniec pracy
            
            // Obudź inne wątki by mogły sprawdzić warunek zakończenia
            {
                std::lock_guard<std::mutex> lock(heapMutex);
                cv.notify_all();
            }
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        threads.emplace_back(worker);
    }
    
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    timeList = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    int* distanceNew = new int[nodes];
    for (int i = 0; i < nodes; i++) {
        distanceNew[i] = distance[i].load(); 
    }

    printResultDistance(graph, nodes, distanceNew);
    printResultPath(graph, nodes, distanceNew, previous);

    delete[] visited;
    delete[] distanceNew;
    delete[] previous;
}

