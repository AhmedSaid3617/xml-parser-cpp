#include <cassert>
#include <string>
#include <iostream>

#include "graph/Graph.h"
#include "graph/DynamicArray.h"

using namespace std;

int main() {
    // dynamic array tests
    DynamicArray<string> arr(2);
    assert(arr.get_capacity() == 2);
    assert(arr.get_consumed() == 0);

#define STRING1 "Test string 1"
#define STRING2 "Another test string 2"
#define STRING3 "Yet, another test string 3"

    string e1 = STRING1;
    string e2 = STRING2;
    string e3 = STRING3;

    arr.add(&e1);
    assert(arr.get_capacity() == 2);
    assert(arr.get_consumed() == 1);

    arr.add(&e2);
    assert(arr.get_capacity() == 2);
    assert(arr.get_consumed() == 2);

    arr.add(&e3);
    assert(arr.get_capacity() == 4);
    assert(arr.get_consumed() == 3);

    assert(arr.get(0) == &e1);
    assert(arr.get(1) == &e2);
    assert(arr.get(2) == &e3);

    // graph tests
    Graph<int> graph;
    uint32_t key0 = graph.add_vertex(new int (100));
    uint32_t key1 = graph.add_vertex(new int (200));

    graph.add_edge(new Edge(graph.get_vertex(key0), graph.get_vertex(key1)));

    cout << "Tests Finished Successfully";

    return 0;
}