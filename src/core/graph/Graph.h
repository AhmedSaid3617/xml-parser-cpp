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
private:
    Vertex<T> * a ;
    Vertex<T> * b;
};

/**
 * @brief vertex that holds it's data and it's adjacent vertices
 * @note uses DynamicArray to hold edges to other vertices
 * @tparam T
 */
template<class T>
class Vertex: public DynamicArray<Edge<T>> {
public:
    void add_edge(Edge<T> edge);
};


/**
 * @brief unweighted, undirected Graph using Adjacency List
 * @note uses DynamicArray to hold vertices
 * @tparam T
 */
template<class T>
class Graph: public DynamicArray<Vertex<T>>{

public:
    unsigned int add_vertex(T * vertex);
    void add_edge(Edge<T> edge);
};


#endif //XML_PARSER_GRAPH_H
