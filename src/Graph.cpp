#include "Graph.h"
#include <queue>

Graph::Graph(int size) : n(size)
{
    adj_matrix.resize(n, vector<int>(n, false));
}

Graph::Graph(const Graph& other) : n(other.n), adj_matrix(other.adj_matrix)
{
}

/*******************************************************************************
* Name: isConnected
* Input: None
* Output: A bool indicating if the graph is connected
* Description: Checks if the graph is connected using BFS
*******************************************************************************/
bool Graph::isConnected() const
{
    if (n == 0) return true;

    vector<bool> visited(n, false);
    queue<int> q;

    // BFS
    q.push(0);
    visited[0] = true;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int i = 0; i < n; i++)
        {
            // Exists an edge between v and i, and i wasn't visited
            if ((adj_matrix[v][i] || adj_matrix[i][v]) && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    // if a vertex wasn't visited the graph isn't connected
    for (int v : visited)
    {
        if (!v) return false;
    }
    return true;
}

/*******************************************************************************
* Name: canonicalForm
* Input: None
* Output: A string representing the canonical form of the graph
* Description: Generates a canonical form of the graph by permuting vertices
*              and finding the lexicographically smallest representation.
*******************************************************************************/
string Graph::canonicalForm() const
{
    vector<int> perm(n);
    for (int i = 0; i < n; i++) perm[i] = i;

    string best_canon, canon;
    do {
        canon = "";
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                // Convert adj_matrix to string based on permutation
                canon += adj_matrix[perm[row]][perm[col]] ? '1' : '0';
            }
        }

        if (best_canon.empty() || canon < best_canon)
        {
            best_canon = canon;
        }
    } while (next_permutation(perm.begin(), perm.end())); // Generates the next lexicographically greater permutation

    return best_canon;
}

/*******************************************************************************
* Name: writeToFile
* Input: out_file - output file stream to write the graph
* Output: None
* Description: Writes the graph to the output file in a format taken from "Biological Computation- Ex2.pdf"
*******************************************************************************/
void Graph::writeToFile(ofstream& out_file) const
{
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (adj_matrix[row][col])
            {
                out_file << (row+1) << " " << (col+1) << endl;
            }
        }
    }
}