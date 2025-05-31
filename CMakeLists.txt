cmake_minimum_required(VERSION 3.30)
project(AIZO_2_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(AIZO_2_2 main.cpp
        Algorithms/Algorithms.h
        Algorithms/MSTalg.cpp
        Algorithms/ShortestPathAlg.cpp
        GUI/GUI.h
        GUI/MainMenu.cpp
        GUI/MSTMenu.cpp
        GUI/ShortestPathMenu.cpp
        DataStructures/Graph.h
        Utilities/Utilities.h
        Utilities/FileHandler.cpp
        Utilities/GraphGeneration.cpp
        DataStructures/MinHeap.h
        DataStructures/DisjointSet.h
        DataStructures/Stack.h
        AlgoTest/Tests.h
        AlgoTest/MSTtest.cpp
        AlgoTest/SPTest.cpp
        AlgoTest/GenerateResults.cpp
)
