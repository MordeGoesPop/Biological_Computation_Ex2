#include "utils.h"
#include "Graph.h"

/*******************************************************************************
* Name: dumpOut
* Input: graphs - vector of Graph representing all the possible motifs of size n
         file_name - file path for the output
         n - size of the motifs
* Output: RET_OK on success
* Description: Writes the connected sub_graphs to an output file in a specific format taken from "Biological Computation- Ex2.pdf"
*******************************************************************************/
int dumpOut(const vector<Graph>& graphs, const string& file_name, int n)
{
    ofstream out_file(file_name);
    if (!out_file)
        ERROR("Error opening output file.");

    DEBUG("Writing connected sub_graphs to " << file_name);
    out_file << "n=" << n << "\ncount=" << graphs.size() << endl;

    for (size_t i = 0; i < graphs.size(); i++)
    {
        out_file << "#" << (i + 1) << endl;
        graphs[i].writeToFile(out_file);
    }

    INFO("Generated " << graphs.size() << " different motifs of size " << n);
    return RET_OK;
}

/*******************************************************************************
* Name: dumpOutMotifs
* Input: motifs - vector of Graph of all possible motifs
         counts - vector of amount of motifs of each type in input graph
         file_name - file path for the output
         n - size of the motifs
* Output: RET_OK on success
* Description: Writes the motifs and their counts to an output file in a specific format taken from "Biological Computation- Ex2.pdf"
*******************************************************************************/
int dumpOutMotifs(const vector<Graph>& motifs, const vector<int>& counts, const string& file_name, int n)
{
    ofstream out_file(file_name);
    if (!out_file)
        ERROR("Error opening output file.");

    DEBUG("Writing motifs to " << file_name);
    out_file << "n=" << n << "\ncount=" << motifs.size() << endl;
    int motifs_count = 0;
    for (size_t i = 0; i < motifs.size(); i++)
    {
        motifs_count += counts[i];
        out_file << "#" << (i + 1) << endl;
        out_file << "count=" << counts[i] << endl;
        motifs[i].writeToFile(out_file);
    }

    INFO("Found " << motifs.size() << " different motifs with " << motifs_count << " motifs of size " << n << " found in input graph");
    return RET_OK;
}

/*******************************************************************************
* Name: readGraphFromFile
* Input: file_name - file path containing the input graph
* Output: Graph object representing the graph read from the file
* Description: Reads a graph from a file in the format taken from "Biological Computation- Ex2.pdf"
*******************************************************************************/
Graph readGraphFromFile(const string& file_name)
{
    ifstream file(file_name);
    if (!file)
        ERROR("Failed to open graph file: " << file_name);

    string line;
    vector<pair<int, int>> edges;
    int max_vertex = 0;

    // Read edges from input graph file
    while (getline(file, line))
    {
        // Skip empty and comment lines
        if (line.empty() || line[0] == '#') continue;

        // Parse the line to extract source and destination vertices
        istringstream iss(line);
        int src, dst;
        if (iss >> src >> dst) // Read edges as pairs
        {
            edges.push_back({src, dst});
            max_vertex = max(max_vertex, max(src, dst)); // To determine graph size
        }
    }

    // Create a graph with the edges we read from input graph file
    Graph g(max_vertex);
    for (const auto& edge : edges)
    {
        g.addEdge(edge.first, edge.second);
    }

    return g;
}