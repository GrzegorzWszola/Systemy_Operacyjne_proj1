//
// Created by grzegorz on 6/3/25.
//

#ifndef MINHEAPDIST_H
#define MINHEAPDIST_H

#include "Graph.h"

struct HeapNode {
    int vertex;
    int distance;
    HeapNode(int v = -1, int d = 0) : vertex(v), distance(d) {}
};

class MinHeapDist {
    HeapNode* heapArr;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    void swapNodes(int i, int j) {
        HeapNode temp = heapArr[i];
        heapArr[i] = heapArr[j];
        heapArr[j] = temp;
    }

    void heapifyUp(int i) {
        while (i != 0 && heapArr[parent(i)].distance > heapArr[i].distance) {
            swapNodes(i, parent(i));
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        int smallest = i;

        while (true) {
            int left = leftChild(i);
            int right = rightChild(i);

            if (left < size && heapArr[left].distance < heapArr[smallest].distance) {
                smallest = left;
            }
            if (right < size && heapArr[right].distance < heapArr[smallest].distance) {
                smallest = right;
            }
            if (smallest == i) {
                break;
            }
            swapNodes(i, smallest);
            i = smallest;
        }
    }

public:
    MinHeapDist(int cap) {
        capacity = cap;
        heapArr = new HeapNode[cap];
        size = 0;
    }

    ~MinHeapDist() {
        delete[] heapArr;
    }

    HeapNode getMinElement() {
        if (size <= 0) {
            throw std::runtime_error("Heap is empty");
        }
        HeapNode root = heapArr[0];
        heapArr[0] = heapArr[--size];
        if (size > 0) {
            heapifyDown(0);
        }
        return root;
    }

    void insertElement(int vertex, int distance) {
        if (size == capacity) {
            throw std::runtime_error("Heap overflow");
        }

        heapArr[size] = HeapNode(vertex, distance);
        heapifyUp(size);
        size++;
    }

    bool empty() {
        return size == 0;
    }
};


#endif //MINHEAPDIST_H
