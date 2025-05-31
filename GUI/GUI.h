#ifndef GUI_H
#define GUI_H
#include <cstdlib>
#include <chrono>
#include "../Utilities/Utilities.h"
#include "../DataStructures/Graph.h"

using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#define PAUSE_SYSTEM "pause"
#else
#define CLEAR_SCREEN "clear"
#endif

static void pause() {
#ifdef _WIN32
    system(PAUSE_SYSTEM);
#else
    cin.ignore();
    cout << "Nacisnij Enter aby kontynuowac...";
    cin.get();
#endif
}

static void clearScreen() {
    system(CLEAR_SCREEN);
}


#include "../DataStructures/Graph.h"

class MainMenu {
public:
    static void entryMessage();
    static void readFromFileGUI(Graph* &graph);
    static void generateGraphGUI(Graph* &graph);
};

class MSTMenu {
public:
    static void menu(Graph* &graph, std::chrono::milliseconds timeMatrix, std::chrono::milliseconds timeList);

};

class ShortestPathMenu {
public:
    static void menu(Graph* &graph, std::chrono::milliseconds timeMatrix, std::chrono::milliseconds timeList);
};

#endif //GUI_H
