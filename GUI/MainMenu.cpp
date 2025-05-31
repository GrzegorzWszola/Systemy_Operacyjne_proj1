
#include "GUI.h"
#include "../Algorithms/Algorithms.h"

void MainMenu::entryMessage() {
    while (true) {
        clearScreen();
        string input;
        chrono::milliseconds timeMatrix = chrono::milliseconds{0}, timeList = chrono::milliseconds{0};
        int choice = 0;
        cout << "1. Najkrotsza sciezka\n2. Drzewo rozpinajace\n3. Wyjdz\nWybierz problem: ";
        cin >> input;

        try {
            choice = stoi(input);
            if (choice > 3 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            pause();
        }

        Graph* graph = nullptr;

        if (choice == 1) ShortestPathMenu::menu(graph, timeMatrix, timeList);
        if (choice == 2) MSTMenu::menu(graph, timeMatrix, timeList);
        if (choice == 3) break;
    }
}

void MainMenu::readFromFileGUI(Graph *&graph) {
    string path;
    cout << "Podaj sciezke do pliku: ";
    cin >> path;

    int** graphData = FileHandler::readFile(path);
    if (graph != nullptr) {
        delete graph;
        graph = nullptr;
    }

    graph = GraphGeneration::createGraphFromFile(graphData);

    graph->printMatrix();
    graph->printList();

    int rows = graphData[0][0];
    for (int i = 0; i <= rows; ++i) delete[] graphData[i];
    delete[] graphData;
}

void MainMenu::generateGraphGUI(Graph* &graph) {
    string nodesInput, densityInput;
    char directedInput;
    int nodes, density;
    bool directed;
    int minCap = 0, maxCap = 10;
    cout << "Podaj ilosc wierzcholkow: ";
    cin >> nodesInput;
    cout << "Podaj gestosc w %: ";
    cin >> densityInput;
    cout << "Czy skierowany [y/n]: ";
    cin >> directedInput;

    try {
        nodes = stoi(nodesInput);
        density = stoi(densityInput);
        if (density < 0 || density > 100) throw invalid_argument("Gestosc w % (0-100)");

        if (tolower(directedInput) == 'y') {
            directed = true;
        } else if (tolower(directedInput) == 'n') directed = false;
          else throw invalid_argument("Podaj y lub n");

    } catch (invalid_argument& e) {
        cout << e.what() << endl;
        return;
    }

    if (graph != nullptr) {
        delete graph;
        graph = nullptr;
    }

    graph = GraphGeneration::createRandomGraph(nodes, density, minCap, maxCap, directed);
}



