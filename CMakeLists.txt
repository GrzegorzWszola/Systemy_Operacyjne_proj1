cmake_minimum_required(VERSION 3.28)
project(Systemy_Op)

set(CMAKE_CXX_STANDARD 20)

add_executable(Systemy_Op
        main.cpp
        Algorithms/Algorithms.h
        Algorithms/ShortestPathAlg.cpp
        DataStructures/Graph.h
        Utilities/Utilities.h
        Utilities/FileHandler.cpp
        Utilities/GraphGeneration.cpp
        DataStructures/MinHeap.h
        DataStructures/DisjointSet.h
        DataStructures/Stack.h
)
