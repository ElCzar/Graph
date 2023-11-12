#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<vector>
#include<list>
#include<utility>
#include<queue>
#include<stack>
#include<iostream>
#include<algorithm>

//Lista de adyacencia
template <class T>
class Graph {
private:
    std::vector<T> vertices;
    std::vector< std::list< std::pair<int,T> > > aristas;
public:
    // Constructor
    Graph();

    // Setter
    void setVertices(std::vector<T> v);
    void setAristas(std::vector< std::list< std::pair<int,T> > > a);

    // Getter
    std::vector<T> getVertices();
    std::vector< std::list< std::pair<int,T> > > getAristas();

    // Quantity
    int cantVertices();
    int cantAristas();

    // Search
    int buscarVertice(T vert);
    bool buscarArista(T ori, T des);

    // Insert
    bool insertVertice(T vert);
    bool insertArista(T ori, T des, int cos);

    // Delete
    bool deleteVertice(T vert);
    bool deleteArista(T ori, T des);

    // Sort
    void sortAristasByVector();
    void sortAristasByCost();

    // Path
    int printPath(std::vector<T> prev, T ori, T des);

    // Walk
    void plain();
    std::vector<T> BFS(T vert);
    std::vector<T> DFS(T vert);
    std::vector<T> Prim(T vert);
    std::vector<T> Dijkstra(T vert);

    // Connections

};

#include "Graph.hxx"

#endif
