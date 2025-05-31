#include "Tests.h"

using namespace std;

void GenerateResults::generateResult() {
    auto timeListAvg = std::chrono::milliseconds{0};
    auto timeMatrixAvg = std::chrono::milliseconds{0};

    int nodes = 1000;
    int density = 20;
    int minCap = 1;
    int maxCap = 1000;
    bool directed = false;

    cout << "Djikstra, DjikstraL, Bellman, BellmanL, Prim, PrimL, Kruskal, KruskalL\n";

    Tests::ShortestPathTestsD(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
    cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << ", ";
    timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};
    Tests::ShortestPathTestsBF(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
    cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << ", ";
    timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};

    Tests::MSTTestsP(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
    cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << ", ";
    timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};
    Tests::MSTTestsK(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
    cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << endl;
    system("pause");
}

