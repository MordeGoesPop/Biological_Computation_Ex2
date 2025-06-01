# Biological_Computation
## Authors: Harel Markel & Eyal Yemini

## Table of Contents
1. [Overview](#-overview)
2. [Compile and Run](#-compile-and-run)
3. [Usage Options](#-usage-options)
4. [Technical Implementation](#-technical-implementation)
5. [Algorithms](#-algorithms)
6. [Answers](#-answers)

---

## 📘 Overview
This software provides functionality for generating and analyzing graph structures. It implements two primary functions:

1. **Question 1:** Generates all possible connected subgraphs of size n.
2. **Question 2:** Identifies and counts motifs (specific subgraph patterns) of size n in a given input graph.

The implementation uses optimized algorithms for graph canonicalization to detect isomorphic structures efficiently.

---

## 📌 Compile and Run

### Compilation
Navigate to the `src/` directory and compile the code using the provided Makefile:

```bash
cd src/
make
```

This will generate the executable file `main`.

### Running the Program
After compilation, run the executable:

```bash
./main
```

The program will prompt you to:
1. Select a question number (1 or 2)
2. Enter the number of vertices (n)

### Example
```
Enter a question to answer (1 or 2):
1
Enter the number of vertices (n):
3
```

The results will be written to output files in the `out/` directory.

### Cleaning Up
To remove all compiled object files and executables, run:

```bash
cd src/
make clean
```

This will delete all `.o` files and the main executable, allowing for a fresh compilation.

---

## 🔍 Usage Options

### Question 1: Generate All Connected Subgraphs
When you choose question 1, the program will:
- Generate all possible connected directed subgraphs with n vertices
- Identify and remove isomorphic graphs
- Output the results to `out/connected_sub_graphs_n<n>.txt`

The output file follows this format:
```
n=3
count=13
#1
1 2
#2
1 2
2 1
...
```

Where each motif starts with a line `#k` followed by its edges, with each edge represented as a line `i j` meaning an edge from vertex i to vertex j.

### Question 2: Find Motifs in a Graph
When you choose question 2, the program will:
- Read an input graph from `input_graph.txt`
- Generate all possible connected subgraphs of size n
- Count occurrences of each motif in the input graph
- Output the results to `out/motifs_n<n>.txt`

The output file follows this format:
```
n=3
count=13
#1
count=1
1 2
1 3
#2
count=1
1 3
2 1
...
```

Where each motif is listed with its count and edge structure.

#### Input Graph Format
The input graph should be specified in `input_graph.txt` in the following format:
```
1 2
2 3
1 4
```

Each line represents an edge from the first vertex to the second vertex. In this example, the graph has 4 vertices with edges from 1→2, 2→3, and 1→4.

### Limitations
For performance reasons, the program limits n to 5 or less. Larger values would result in excessive computation time due to the exponential growth in the number of possible graphs.

---

## Technical Implementation

### Project Structure
- **src/main.cpp**: Main implementation file
- **src/Graph.cpp**: Graph class implementation
- **src/Graph.h**: Graph class header
- **src/utils.cpp**: Utility functions
- **src/utils.h**: Macros, utilities, and helper functions

### Class Overview
- **Graph**: Represents a directed graph with an adjacency matrix representation, includes:
  - Check for connectivity
  - Graph canonicalization to identify isomorphic graphs
  - File I/O for reading and writing graphs

---

## 🧠 Algorithms

### Graph Generation
The program uses bit manipulation to efficiently generate all possible edge combinations, resulting in all possible directed graphs with n vertices. For each graph, it:
1. Checks if the graph is connected
2. Computes a canonical form to identify and remove isomorphic duplicates

### Graph Canonicalization
The canonical form of a graph is a unique string representation that is invariant to vertex permutation. Two graphs are isomorphic if and only if they have the same canonical form. The algorithm:

1. Tries all possible vertex permutations
2. For each permutation, computes a string representation of the adjacency matrix
3. Returns the lexicographically smallest representation

### Motif Finding
To find motifs in a graph:
1. Generate all possible connected subgraphs of size n
2. For each possible subset of n vertices in the input graph:
   - Extract the induced subgraph
   - Check if it's connected
   - Compute its canonical form
   - Increment the counter for the corresponding motif

## 🧮 Answers
Answers to questions in the [Biological Computation- Ex2.pdf](Biological%20Computation-%20Ex2.pdf) file can be found in the [Answers.txt](Answers.txt) file
