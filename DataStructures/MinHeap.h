#ifndef MINHEAP_H
#define MINHEAP_H
#include "Graph.h"

class MinHeap {
    Edge* heapArr;
    int size;
    int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }

    //Function to rebuild heap after inserting element
    void heapifyUp(int i) {
        while (i != 0 && heapArr[parent(i)].weight > heapArr[i].weight) {
            std::swap(heapArr[i], heapArr[parent(i)]);
            i = parent(i);
        }
    }

    //Function to rebuild heap after taking min element
    void heapifyDown(int i) {
        int smallest = i;

        while (true) {
            int left = leftChild(i);
            int right = rightChild(i);
            if (left < size && heapArr[left].weight < heapArr[smallest].weight) {
                smallest = left;
            }
            if (right < size && heapArr[right].weight < heapArr[smallest].weight) {
                smallest = right;
            }
            if (smallest == i) {
                break;
            }
            std::swap(heapArr[i], heapArr[smallest]);
            i = smallest;
        }
    }


public:
    MinHeap(int cap) {
        this->capacity = cap;
        heapArr = new Edge[cap];
        size = 0;
    }

    ~MinHeap() {
        delete[] heapArr;
    }

    //Function to get min value from heap
    Edge getMinElement() {
        if (size <= 0) {
            throw std::runtime_error("Heap is empty");
        }
        Edge root = heapArr[0];
        heapArr[0] = heapArr[--size];
        if (size > 0) {
            heapifyDown(0);
        }
        return root;
    }


    //Function for inserting elements to min heap
    void insertElement(const Edge &value) {
        if (size == capacity) {
            std::cout << "Heap overflow\n";
            return;
        }

        heapArr[size] = Edge(value);
        heapifyUp(size);
        size++;
    }

    void bulkInsert(const Edge* arr, int s) {
        for (int i = 0; i < s; i++) {
            heapArr[size + i] = arr[i];
        }
        size += s;
        for (int i = 0; i < s; i++) {
            heapArr[size + i] = arr[i];
        }
    }

    bool empty() {
        if (size == 0) return true;
        return false;
    }
};

#endif //MINHEAP_H
