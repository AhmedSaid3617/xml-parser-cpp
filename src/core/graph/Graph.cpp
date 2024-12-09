#include "Graph.h"

template<class T>
void Vertex<T>::add_edge(Edge<T> edge) {
    add(edge);
}

template<class T>
void Graph<T>::add_edge(Edge<T> edge) {
    edge.a->add_edge(edge);
    edge.b->add_edge(edge);
}

template<class T>
unsigned int Graph<T>::add_vertex(T * vertex) {
    add(vertex);
}