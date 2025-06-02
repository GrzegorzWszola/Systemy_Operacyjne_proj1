#include "Tests.h"

using namespace std;

void GenerateResults::generateResult() {
    auto timeListAvg = std::chrono::milliseconds{0};
    auto timeMatrixAvg = std::chrono::milliseconds{0};

    int nodes = 1000;
    int density = 99;
    int minCap = 1;
    int maxCap = 1000;
    bool directed = true;

    cout << "Djikstra, DjikstraL, Bellman, BellmanL, Prim, PrimL, Kruskal, KruskalL\n";

    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            density = 20;
        } else if (i == 1) {
            density = 60;
        } else {
            density = 99;
        }
        cout << "[";
        Tests::ShortestPathTestsD(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
        cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << ", ";
        timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};
        Tests::ShortestPathTestsBF(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
        cout << timeMatrixAvg.count() << ", " << timeListAvg.count(); // << ", "
        timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};

        Tests::MSTTestsP(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
        cout << timeMatrixAvg.count() << ", " << timeListAvg.count() << ", ";
        timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};
        Tests::MSTTestsK(timeListAvg, timeMatrixAvg, nodes, density, minCap, maxCap, directed);
        cout << timeMatrixAvg.count() << ", " << timeListAvg.count();
        timeMatrixAvg = std::chrono::milliseconds{0}; timeListAvg = std::chrono::milliseconds{0};
        cout << "], ";
    }
    cout << "Naciśnij enter aby kontynuować...\n";
    getchar();
}

