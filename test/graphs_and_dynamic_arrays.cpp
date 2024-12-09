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
    (void) graph.add_vertex(new int (100));
    (void) graph.add_vertex(new int (200));
    (void) graph.add_vertex(new int (300));
    (void) graph.add_vertex(new int (400));

    assert(*graph.get_vertex(0)->get_data() == 100);
    assert(*graph.get_vertex(1)->get_data() == 200);
    assert(*graph.get_vertex(2)->get_data() == 300);
    assert(*graph.get_vertex(3)->get_data() == 400);

    graph.add_edge(new Edge(graph.get_vertex(0), graph.get_vertex(1)));
    graph.add_edge(new Edge(graph.get_vertex(0), graph.get_vertex(2)));
    graph.add_edge(new Edge(graph.get_vertex(0), graph.get_vertex(3)));
    graph.add_edge(new Edge(graph.get_vertex(2), graph.get_vertex(3)));
    graph.add_edge(new Edge(graph.get_vertex(1), graph.get_vertex(3)));

    assert(graph.get_vertex(0)->get_edge(0)->b == graph.get_vertex(1));
    assert(graph.get_vertex(0)->get_edge(1)->b == graph.get_vertex(2));
    assert(graph.get_vertex(0)->get_edge(2)->b == graph.get_vertex(3));

    cout << "Tests Finished Successfully";

    return 0;
}