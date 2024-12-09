#include <cassert>
#include <string>
#include <iostream>

//#include "graph/Graph.h"
#include "graph/DynamicArray.h"

using namespace std;

int main() {
    DynamicArray<int> arr;
    arr.add(new int(3));
//    Graph<int> graph;
//    uint32_t key0 = graph.add_vertex(new int (100));
//    uint32_t key1 = graph.add_vertex(new int (200));
//
//    graph.add_edge(new Edge(graph.get_vertex(key0), graph.get_vertex(key1)));

    cout << *arr.get(0) << endl;

    return 0;
}