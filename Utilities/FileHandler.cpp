
#include "Utilities.h"
int **FileHandler::readFile(std::string fileName) {
    if (!fileName.empty() && fileName.front() == '"' && fileName.back() == '"') {
        fileName = fileName.substr(1, fileName.length() - 2);
    }
    std::ifstream file(fileName);
    std::string line, edges;
    std::string tempString;
    int** list;

    if (!file) {
        std::cout << "Nie mozna otworzyc pliku!\n";
    }

    std::getline(file, line);
    std::istringstream iss(line);
    iss >> tempString;
    list = new int*[std::stoi(tempString) + 1];
    list[0] = new int[4];
    list[0][0] = std::stoi(tempString);
    for (int i = 1; i < std::stoi(tempString)+1; i++) {
        list[i] = new int[3];
    }

    int i = 1;
    while (iss >> tempString) {
        list[0][i] = std::stoi(tempString);
        i++;
    }
    //Adding -1 template to check for what type of graph
    if (i == 2) {
        list[0][2] = -1;
        list[0][3] = -1;
    }
    if (i == 3) {
        list[0][3] = -1;
    }

    i = 1;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> list[i][0] >> list[i][1] >> list[i][2];
        i++;
    }
    return list;
}

