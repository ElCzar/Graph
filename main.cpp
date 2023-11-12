#include <iostream>
#include "Graph.h"
#include <vector>
#include <list>
#include <utility>
#include <algorithm>

int main() {
    Graph<char> *g = new Graph<char>();
    g->insertVertice('A');
    g->insertVertice('C');
    g->insertVertice('J');
    g->insertVertice('Y');
    g->insertVertice('N');
    g->insertVertice('Z');
    g->insertVertice('X');
    g->insertVertice('E');

    g->insertArista('A', 'X', 3);
    g->insertArista('X', 'A', 3);

    g->insertArista('A', 'N', 5);
    g->insertArista('N', 'A', 5);

    g->insertArista('A', 'J', 4);
    g->insertArista('J', 'A', 4);

    g->insertArista('A', 'E', 4);
    g->insertArista('E', 'A', 4);

    g->insertArista('J', 'C', 2);
    g->insertArista('C', 'J', 2);

    g->insertArista('C', 'Y', 8);
    g->insertArista('Y', 'C', 8);

    g->insertArista('Y', 'N', 5);
    g->insertArista('N', 'Y', 5);

    g->insertArista('N', 'Z', 4);
    g->insertArista('Z', 'N', 4);

    g->insertArista('Z', 'X', 1);
    g->insertArista('X', 'Z', 1);

    g->insertArista('X', 'Y', 6);
    g->insertArista('Y', 'X', 6);

    g->sortAristasByCost();
    g->sortAristasByVector();

    std::cout << "Plano: ";
    g->plain();

    std::cout << "DFS: ";
    std::vector<char> dfs = g->DFS('A');
    std::cout << "BFS: ";
    std::vector<char> bfs = g->BFS('A');
    std::cout << "Prim: ";
    std::vector<char> prim = g->Prim('A');
    std::cout << "Dijkstra: ";
    std::vector<char> dijkstra = g->Dijkstra('A');

    std::cout << "Camino DFS A->Y: ";
    int cotsDFS = g->printPath(dfs, 'A', 'Y');
    std::cout << "Camino BFS A->Y: ";
    int cotsBFS = g->printPath(bfs, 'A', 'Y');
    std::cout << "Camino Prim A->Y: ";
    int cotsPrim = g->printPath(prim, 'A', 'Y');
    std::cout << "Camino Dijkstra A->Y: ";
    int cotsDijkstra = g->printPath(dijkstra, 'A', 'Y');

    std::cout << "Costo DFS: " << cotsDFS << std::endl;
    std::cout << "Costo BFS: " << cotsBFS << std::endl;
    std::cout << "Costo Prim: " << cotsPrim << std::endl;
    return 0;
}

