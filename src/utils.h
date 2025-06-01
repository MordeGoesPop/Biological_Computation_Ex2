#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;
class Graph;

#define RESET_COLOR  "\033[0m"
#define RED_COLOR    "\033[31m"
#define GREEN_COLOR  "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR   "\033[34m"

#define INFO_1(x) INFO_2(x, GREEN_COLOR)
#define INFO_2(x, color) do { cout << color << x << RESET_COLOR << endl; } while (0)
#define GET_INFO_MACRO(_1, _2, NAME, ...) NAME
#define INFO(...) GET_INFO_MACRO(__VA_ARGS__, INFO_2, INFO_1)(__VA_ARGS__)

#define ERROR(x) \
    do { cerr << RED_COLOR << "Error: " << x << RESET_COLOR << endl; exit(1); } while (0)
#define WARNING(x) \
    do { cerr << YELLOW_COLOR << "Warning: " << x << RESET_COLOR << endl; } while (0)
#define DEBUG(x) \
    do { cout << BLUE_COLOR << "Debug: " << x << RESET_COLOR << endl; } while (0)

#define BIT_MASK(bit) (1ULL << (bit))
#define MS_TO_SEC(ms) ((ms) / 1000.0)

#define GET_END_TIME() \
    auto end_time = chrono::high_resolution_clock::now();
#define GET_START_TIME() \
    auto start_time = chrono::high_resolution_clock::now();
#define GET_DURATION() \
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
#define GET_TIMING() \
    GET_END_TIME() \
    GET_DURATION() \
    DEBUG("Time taken: " << duration << "ms = " << MS_TO_SEC(duration) << "s");

enum {
    RET_OK = 0,
    RET_ERR = 1
};

int dumpOut(const vector<Graph>& graphs, const string& file_name, int n);
int dumpOutMotifs(const vector<Graph>& motifs, const vector<int>& counts, const string& file_name, int n);
Graph readGraphFromFile(const string& file_name);

#endif // UTILS_H