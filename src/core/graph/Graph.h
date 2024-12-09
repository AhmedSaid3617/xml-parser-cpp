//
// Created by Shams El-Din Abdel-Monem on 09/12/2024.
//

#ifndef XML_PARSER_GRAPH_H
#define XML_PARSER_GRAPH_H

#include <cstdint>
#include "DynamicArray.h"

template<class T> class Vertex;

/**
 * @brief edge between two vertices
 * @tparam T
 */
template<class T>
class Edge {
public:
    Vertex<T> * a ;
    Vertex<T> * b;

    Edge(Vertex<T> * a, Vertex<T> * b): a(a), b(b) {
    }
};

/**
 * @brief vertex that holds it's data and it's adjacent vertices
 * @note inherits DynamicArray to hold edges to other vertices
 * @tparam T
 */
template<class T>
class Vertex {
private:
    T * data;
    DynamicArray<Edge<T>> * edges;

public:
    explicit Vertex(T * data, uint32_t capacity = 100);
    void add_edge(Edge<T> * edge);

    Edge<T> * get_edge(uint32_t index) {
        return edges->get(index);
    }

    uint32_t get_edges_count() {
        return edges->get_consumed();
    }

    T * get_data() {
        return data;
    }
};


/**
 * @brief unweighted, undirected Graph using Adjacency List
 * @note uses DynamicArray to hold vertices, it should not inherit
 * as this will be array inside array problem
 * @tparam T
 */
template<class T>
class Graph {
private:
    DynamicArray<Vertex<T>> * vertices;

public:
    explicit Graph(uint32_t capacity = 100);
    uint32_t add_vertex(T * vertex);
    Vertex<T> * get_vertex(uint32_t index);

    uint32_t get_vertices_count() {
        return vertices->get_consumed();
    }

    void add_edge(Edge<T> * edge);
};

template<class T>
Vertex<T> * Graph<T>::get_vertex(uint32_t index) {
    return vertices->get(index);
}

template<class T>
Graph<T>::Graph(uint32_t capacity) {
    vertices = new DynamicArray<Vertex<T>>(capacity);
}

template<class T>
Vertex<T>::Vertex(T * data, uint32_t capacity): data(data) {
    edges = new DynamicArray<Edge<T>>(capacity);
}

template<class T>
void Vertex<T>::add_edge(Edge<T> * edge) {
    edges->add(edge);
}

template<class T>
void Graph<T>::add_edge(Edge<T> * edge) {
    edge->a->add_edge(edge);
    edge->b->add_edge(edge);
}

template<class T>
uint32_t Graph<T>::add_vertex(T * vertex) {
    return vertices->add(new Vertex(vertex));
}

#endif //XML_PARSER_GRAPH_H
