#ifndef DISJOINTSET_H
#define DISJOINTSET_H

class DisjointSet {
    int* parent;
    int* size;

public:
    DisjointSet(int p) {
        parent = new int[p];
        size = new int[p];
        for (int i = 0; i < p; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    ~DisjointSet() {
        delete[] parent;
        delete[] size;
    }

    //Finding the root of the graph
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }


    //Unioning 2 graphs together based on size
    void unionBySize(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV)
            return;

        //Attach the smaller tree under the larger tree
        if (size[rootU] < size[rootV]) {
            parent[rootU] = rootV;
            size[rootV] += size[rootU];
        } else {
            parent[rootV] = rootU;
            size[rootU] += size[rootV];
        }
    }

};

#endif //DISJOINTSET_H
