
#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

class Graph {
private:
    int n;  // #vertices
    vector<vector<int>> adj_matrix;

public:
    Graph(int size);
    Graph(const Graph& other);

    void addEdge(int row, int col) { adj_matrix[row-1][col-1] = true; }
    bool hasEdge(int u, int v) const { return adj_matrix[u-1][v-1]; }
    int getSize() const { return n; }

    bool isConnected() const;
    string canonicalForm() const;
    void writeToFile(ofstream& out_file) const;
};

#endif // GRAPH_H