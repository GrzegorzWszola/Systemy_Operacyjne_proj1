
#include "GUI.h"
#include "../Algorithms/Algorithms.h"
#include "../Utilities/Utilities.h"

void MSTMenu::menu(Graph* &graph, std::chrono::milliseconds timeMatrix, std::chrono::milliseconds timeList) {
    string input;

    while (true) {
        clearScreen();
        int choice = 0;
        cout << "1. Wczytaj z pliku\n2. Wygeneruj losowy graf\n3. Wyswietl listowo i macierzowo\n4. Algorytm Prima\n5. Kruskal\n6. Wyswietl wyniki\n7. Wyjdz\nWybierz opcje: ";
        cin >> input;

        try {
            choice = stoi(input);
            if (choice > 7 || choice <= 0) throw invalid_argument("Wybierz mozliwa liczbe");
        } catch (invalid_argument& e) {
            cout << e.what() << endl;
            pause();
            continue;
        }

        if (choice == 1) {
            if (graph != nullptr) {
                delete graph;
                graph = nullptr;
            }
            MainMenu::readFromFileGUI(graph);
            bool directed = graph->isDirected();
            pause();
        }
        if (choice == 2) {
            if (graph != nullptr) {
                delete graph;
                graph = nullptr;
            }
            MainMenu::generateGraphGUI(graph);
            pause();
        }
        if (choice == 3) {
            graph->printMatrix();
            graph->printList();
            pause();
        }
        if (choice == 4) {
            MSTAlgorithms::prim(graph, timeMatrix);
            MSTAlgorithms::primList(graph, timeList);
            cout << "Wyniki: " << timeMatrix << endl;
            cout << "Wyniki: " << timeList << endl;
            pause();
        }

        if (choice == 5) {
            MSTAlgorithms::kruskal(graph, timeMatrix);
            MSTAlgorithms::kruskalList(graph, timeList);
            cout << "Wyniki: " << timeMatrix << endl;
            cout << "Wyniki: " << timeList << endl;
            pause();
        }

        if (choice == 6) {
            MSTAlgorithms::prim(graph, timeMatrix);
            MSTAlgorithms::primList(graph, timeList);
            cout << "Wyniki: " << timeMatrix << endl;
            cout << "Wyniki: " << timeList << endl;
            pause();

            MSTAlgorithms::kruskal(graph, timeMatrix);
            MSTAlgorithms::kruskalList(graph, timeList);
            cout << "Wyniki: " << timeMatrix << endl;
            cout << "Wyniki: " << timeList << endl;
            pause();
        }

        if (choice == 7) {
            delete graph;
            break;
        }
    }
}




