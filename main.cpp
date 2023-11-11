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

    g->insertVertice('A', 'X', 3);
    g->insertVertice('X', 'A', 3);

    g->insertVertice('A', 'N', 5);
    g->insertVertice('N', 'A', 5);

    g->insertVertice('A', 'J', 4);
    g->insertVertice('J', 'A', 4);

    g->insertVertice('A', 'E', 4);
    g->insertVertice('E', 'A', 4);

    g->insertVertice('J', 'C', 2);
    g->insertVertice('C', 'J', 2);

    g->insertVertice('C', 'Y', 8);
    g->insertVertice('Y', 'C', 8);

    g->insertVertice('Y', 'N', 5);
    g->insertVertice('N', 'Y', 5);

    g->insertVertice('N', 'Z', 4);
    g->insertVertice('Z', 'N', 4);

    g->insertVertice('Z', 'X', 1);
    g->insertVertice('X', 'Z', 1);

    g->insertVertice('X', 'Y', 6);
    g->insertVertice('Y', 'X', 6);

    g->sortAristasByCost();
    g->sortAristasByVector();

    std::cout << "Plano: ";
    g->plain();

    std::cout << "DFS: ";
    std::vector<char> dfs = g->DFS('A');
    std::cout << "BFS: ";
    std::vector<char> bfs = g->BFS('A');

    std::cout << "Camino DFS A->Y: ";
    int cotsDFS = g->printPath(dfs, 'A', 'Y');
    std::cout << "Camino BFS A->Y: ";
    int cotsBFS = g->printPath(bfs, 'A', 'Y');

    std::cout << "Costo DFS: " << cotsDFS << std::endl;
    std::cout << "Costo BFS: " << cotsBFS << std::endl;
    return 0;
}

