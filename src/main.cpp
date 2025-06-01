#include "Graph.h"
#include "utils.h"
#include <chrono>
#include <unordered_set>
#include <map>

/*******************************************************************************
* Name: genAllGraphs
* Input: n - number of vertices in the sub_graphs
         results - vector of the generated connected sub_graphs of size n
* Output: None
* Description: Generates all connected sub_graphs of size n by iterating through all possible edge combinations
*******************************************************************************/
void genAllGraphs(int n, vector<Graph>& results)
{
    int max_edges = n * (n - 1);

    // For fast canonial form search
    unordered_set<string> canonical_forms;

    // Create an edge list for easy reference
    vector<pair<int, int>> edges;
    for (int row = 1; row <= n; row++)
    {
        for (int col = 1; col <= n; col++)
        {
            if (row != col) // Skip self-loops
            {
                edges.push_back({row, col});
            }
        }
    }

    for (unsigned long long mask = 1; mask < BIT_MASK(max_edges); mask++)
    {
        Graph g(n);

        // Add edges based on the bit mask
        for (size_t i = 0; i < edges.size(); i++)
        {
            if (mask & BIT_MASK(i))
            {
                g.addEdge(edges[i].first, edges[i].second);
            }
        }

        if (g.isConnected())
        {
            // Canonical form for isomorphism checking
            string canonical = g.canonicalForm();

            if (canonical_forms.find(canonical) == canonical_forms.end())
            {
                canonical_forms.insert(canonical);
                results.push_back(g);
            }
        }
    }
}

/*******************************************************************************
* Name: findMotifsInGraph
* Input: n - motif size to search for in the input graph
         input_graph - graph for motifs search
         motifs_graph_n - vector of the generated motifs of size n
         motifs_count - vector to store the count of each motif found
* Output: None
* Description: Finds all motifs of size n in the input graph by generating all possible subgraphs of size n
               and checking if they match any of the pre-generated motifs.
               This is done by generating all combinations of n vertices from the input graph,
               creating a subgraph from these vertices, and checking if the subgraph is connected.
               If the subgraph is connected, its canonical form is checked against the pre-generated motifs.
*******************************************************************************/
void findMotifsInGraph(int n, Graph& input_graph, vector<Graph>& motifs_graph_n, vector<int>& motifs_count)
{
    int input_size = input_graph.getSize();
    if (n > input_size)
        ERROR("The motif size (n = " << n << ") is greater than the input graph size.");

    genAllGraphs(n, motifs_graph_n);

    // Map between canonical form and motif number and add possible motifs of size n to the map
    map<string, int> canonical_to_index;
    for (size_t i = 0; i < motifs_graph_n.size(); i++)
    {
        canonical_to_index[motifs_graph_n[i].canonicalForm()] = i;
    }

    motifs_count.resize(motifs_graph_n.size(), 0);

    // All vertex IDs in the input graph
    vector<int> vertices(input_size);
    for (int i = 0; i < input_size; i++)
    {
        vertices[i] = i + 1;
    }

    vector<bool> selected_vertices(input_size, false);
    // Select first n vertices
    for (int i = 0; i < n; i++)
    {
        selected_vertices[i] = true;
    }

    do {
        Graph sub_graph(n);
        vector<int> vertex_mapping(input_size + 1, 0);

        // Mapping from original vertex IDs to 1,2,...,n
        int new_id = 1;
        for (int i = 0; i < input_size; i++)
        {
            if (selected_vertices[i])
                vertex_mapping[vertices[i]] = new_id++;
        }

        // Add edges between selected_vertices
        for (int i = 0; i < input_size; i++)
        {
            if (selected_vertices[i])
            {
                for (int j = 0; j < input_size; j++)
                {
                    if (selected_vertices[j] && input_graph.hasEdge(vertices[i], vertices[j]))
                        sub_graph.addEdge(vertex_mapping[vertices[i]], vertex_mapping[vertices[j]]);
                }
            }
        }

        if (sub_graph.isConnected())
        {
            string canonical = sub_graph.canonicalForm();
            // Check if the canonical form exists in the motifs map
            if (canonical_to_index.count(canonical))
            {
                motifs_count[canonical_to_index[canonical]]++;
            }
        }

    } while (prev_permutation(selected_vertices.begin(), selected_vertices.end())); // Generates the previous lexicographically smaller permutation
}

int main()
{
    int n = 0, question = 1;
    vector<Graph> motifs_graph_n;

    do {
        INFO("Enter a question to answer (1 or 2): ");
        cin >> question;
        INFO("Enter the number of vertices (n): ");
        cin >> n;

        if (n <= 0 || question < 1 || question > 2)
            ERROR("Invalid input, please enter (n > 0), (question = 1 || question = 2)");

        if (n <= 5) // Limit to n <= 5 to avoid excessive computation
        {
            GET_START_TIME();

            switch (question)
            {
                case 1:
                {
                    genAllGraphs(n, motifs_graph_n);
                    GET_TIMING();
                    string file_name = "../out/connected_sub_graphs_n" + to_string(n) + ".txt";
                    return dumpOut(motifs_graph_n, file_name, n);
                }
                case 2:
                {
                    string input_file = "input_graph.txt";
                    DEBUG("Input Graph File: " << input_file);
                    Graph input_graph = readGraphFromFile(input_file);

                    vector<int> motifs_count;
                    findMotifsInGraph(n, input_graph, motifs_graph_n, motifs_count);

                    GET_TIMING();
                    string file_name = "../out/motifs_n" + to_string(n) + ".txt";
                    return dumpOutMotifs(motifs_graph_n, motifs_count, file_name, n);
                }
                default:
                {
                    WARNING("Invalid question number. Please enter 1 or 2.");
                    break;
                }
            }
        }
        else
        {
            WARNING("Please use (n <= 5) to avoid excessive computation.");
        }
    } while (true);

    INFO("Thank you for enjoying our program for this amazing course learning what is the power house of the cell #mitochondria.", GREEN_COLOR);
    return RET_OK;
}
