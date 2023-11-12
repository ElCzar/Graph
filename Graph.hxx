#include "Graph.h"

// Constructor
template <class T>
Graph<T>::Graph() {
    vertices = std::vector<T>();
    aristas = std::vector< std::list< std::pair<int,T> > >();
}


// Setter
template <class T>
void Graph<T>::setVertices(std::vector<T> v) {
    vertices = v;
}

template <class T>
void Graph<T>::setAristas(std::vector< std::list< std::pair<int,T> > > a) {
    aristas = a;
}

// Getter
template <class T>
std::vector<T> Graph<T>::getVertices() {
    return vertices;
}

template <class T>
std::vector< std::list< std::pair<int,T> > > Graph<T>::getAristas() {
    return aristas;
}

// Quantity
template <class T>
int Graph<T>::cantVertices() {
    return vertices.size();
}

template <class T>
int Graph<T>::cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
        suma += aristas[i].size();
    }
    return suma;
}

// Search
template <class T>
int Graph<T>::buscarVertice(T vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
        if (vertices[i] == vert)  ind = i;
    }
    return ind;
}

template <class T>
bool Graph<T>::buscarArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);

    if ( i_ori != -1 && i_des != -1 ) {

        std::list<std::pair<int,T>> aristasOri = aristas[i_ori];
        typename std::list< std::pair<int,T> >::iterator itList = aristasOri.begin();
        typename std::list< std::pair<int,T> >::iterator itListEnd = aristasOri.end();

        for (; itList != itListEnd; itList++) {
            std::pair<int,T> vertDes = *itList;
            int i_vertDes = buscarVertice(vertDes.second);

            if (i_vertDes == i_des)  return true;
        }
    }

    return res;
}

// Insert
template <class T>
bool Graph<T>::insertVertice(T vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
        this->vertices.push_back(vert);
        this->aristas.push_back(std::list<std::pair<int,T>>());
        res = true;
    }
    return res;
}

template <class T>
bool Graph<T>::insertArista(T ori, T des, int cos) {
    bool res = false;
    if(!buscarArista(ori, des)) {
        int i_ori = buscarVertice(ori);
        int i_des = buscarVertice(des);

        aristas[i_ori].push_back(std::pair<int,T>(cos, des));
        res = true;
    }
    return res;
}

// Delete
template <class T>
bool Graph<T>::deleteVertice(T vert) {
    bool res = false;
    int i_vert = buscarVertice(vert);

    if( i_vert == -1) return res;

    typename std::vector< std::list< std::pair<int,T> > >::iterator itA, posE, itE;
    itA = aristas.begin();
    itE = aristas.end();

    int ind = 0;
    for (; itA != itE; itA++, ind++) {

        if (ind == i_vert) {
            posE = itA;
        } else {
            typename std::list< std::pair<int,T> >::iterator itList, posEE, itListEnd;
            std::list< std::pair<int,T> > list = *itA;
            itList = list.begin();
            itListEnd = list.end();
            bool encontrado = false;

            for (; itList != itListEnd; itList++) {
                std::pair<int,T> vertDes = *itList;
                int i_vertDes = buscarVertice(vertDes.second);

                if (i_vertDes == i_vert) {
                    posEE = itList;
                    encontrado = true;
                }
            }

            if (encontrado) itA->erase(posEE);
        }

    }

    aristas.erase(posE);
    vertices.erase(vertices.begin() + i_vert);

    res = true;
    return res;
}

template <class T>
bool Graph<T>::deleteArista(T ori, T des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if ( i_ori != -1 && i_des != -1 ) {
        typename std::list< std::pair<int,T> >::iterator itList = aristas[i_ori].begin();
        for (; itList != aristas[i_ori].end(); itList++) {
            std::pair<int,T> vertDes = *itList;
            int i_vertDes = buscarVertice(vertDes.second);

            if (i_vertDes == i_des) {
                aristas[i_ori].erase(itList);
                res = true;
                break;
            }
        }
    }
    return res;
}

// Sort
template <class T>
void Graph<T>::sortAristasByVector() {
    for (int i = 0; i < cantVertices(); i++) {
        aristas[i].sort(
                [](std::pair<int,T> &a, std::pair<int,T> &b) {
                    return a.second < b.second;
                }
        );

    }
}

template <class T>
void Graph<T>::sortAristasByCost() {
    for (int i = 0; i < cantVertices(); i++) {
        aristas[i].sort(
                [](std::pair<int,T> &a, std::pair<int,T> &b) {
                    return a.first < b.first;
                }
        );

    }
}

// Path
template <class T>
int Graph<T>::printPath(std::vector<T> prev, T ori, T des) {
    int pathCost = 0;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);

    if (i_ori == -1 || i_des == -1 || prev[i_ori] != vertices[i_ori]) {
        std::cout << "No existe el camino vector vacio" << std::endl;
        return 0;
    }

    std::vector<T> camino;
    int i_sig = i_des;
    while (i_sig != i_ori) {
        camino.push_back(vertices[i_sig]);
        int i_ant = i_sig;
        i_sig = buscarVertice(prev[i_sig]);

        typename std::list< std::pair<int,T> >::iterator itList = aristas[i_sig].begin();
        for (; itList != aristas[i_sig].end(); itList++) {
            std::pair<int,T> vertDes = *itList;
            int i_vertDes = buscarVertice(vertDes.second);

            if (i_vertDes == i_ant) {
                pathCost += vertDes.first;
                break;
            }
        }
    }
    camino.push_back(vertices[i_sig]);

    for (int i = camino.size() - 1; i >= 0; i--) {
        std::cout << camino[i] << " ";
    }
    std::cout << std::endl;

    return pathCost;
}

// Walk
template <class T>
void Graph<T>::plain() {
    for (int i = 0; i < cantVertices(); i++) {
        std::cout << vertices[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
std::vector<T> Graph<T>::BFS(T vert) {
    // Lista de predecesores para poder luego hacer caminos
    std::vector<T> resultado;
    resultado.resize(cantVertices(), T());

    std::vector<bool> visitados;

    int i_vert = buscarVertice(vert);

    if (i_vert == -1) {
        return resultado;
    }

    visitados.resize(cantVertices(), false);

    // Cola de pares <Vertice, Padre>
    std::queue<std::pair<int,int>> cola;
    std::pair<int, int> par = std::make_pair(i_vert, i_vert);
    cola.push(par);

    while (!cola.empty()) {
        std::pair<int,int> parActual = cola.front();
        cola.pop();

        int actual = parActual.first;

        if (!visitados[actual]) {
            std::cout << vertices[actual] << " ";
            visitados[actual] = true;
            int actualPadre = parActual.second;
            resultado[actual] = vertices[actualPadre];

            typename std::list< std::pair<int,T> >::iterator itList = aristas[actual].begin();
            for (; itList != aristas[actual].end(); itList++) {
                std::pair<int,T> vertDes = *itList;
                int i_nSon = buscarVertice(vertDes.second);
                std::pair<int, int> parN = std::make_pair(i_nSon, actual);
                cola.push(parN);
            }
        }
    }
    std::cout << std::endl;

    return resultado;
}

template <class T>
std::vector<T> Graph<T>::DFS(T vert) {
    // Lista de predecesores para poder luego hacer caminos
    std::vector<T> resultado;
    resultado.resize(cantVertices(), T());

    std::vector<bool> visitados;

    int i_vert = buscarVertice(vert);

    if (i_vert == -1) {
        return resultado;
    }

    visitados.resize(cantVertices(), false);

    // Pila de pares <Vertice, Padre>
    std::stack<std::pair<int, int>> pila;
    std::pair<int, int> par = std::make_pair(i_vert, i_vert);
    pila.push(par);

    while (!pila.empty()) {
        std::pair<int,int> parActual = pila.top();
        pila.pop();

        int actual = parActual.first;

        if (!visitados[actual]) {
            std::cout << vertices[actual] << " ";
            visitados[actual] = true;
            int actualPadre = parActual.second;
            resultado[actual] = vertices[actualPadre];

            typename std::list< std::pair<int,T> >::reverse_iterator itList = aristas[actual].rbegin();
            for (; itList != aristas[actual].rend(); itList++) {
                std::pair<int,T> vertDes = *itList;
                int i_nSon = buscarVertice(vertDes.second);
                std::pair<int, int> parN = std::make_pair(i_nSon, actual);
                pila.push(parN);
            }
        }
    }

    std::cout << std::endl;
    return resultado;
}

template <class T>
std::vector<T> Graph<T>::Prim(T vert) {
    // Lista de predecesores para poder luego hacer caminos
    std::vector<T> resultado;
    resultado.resize(cantVertices(), T());

    std::vector<bool> visitados;

    int i_vert = buscarVertice(vert);

    if (i_vert == -1) {
        return resultado;
    }

    visitados.resize(cantVertices(), false);

    // Lista de pares <Padre, <costo, destino> > ordenada por costo
    std::list< std::pair<int, std::pair<int, T> > > aristasDisponibles;
    std::pair<int, T> par = std::make_pair(0, vert);
    std::pair<int, std::pair<int, T> > par2 = std::make_pair(i_vert, par);
    aristasDisponibles.push_back(par2);

    while (!aristasDisponibles.empty()) {
        std::pair<int, std::pair<int, T> > parActual = aristasDisponibles.front();
        aristasDisponibles.pop_front();

        T actualT = parActual.second.second;
        int actual = buscarVertice(actualT);

        if (!visitados[actual]) {
            std::cout << vertices[actual] << " ";
            visitados[actual] = true;

            int actualPadre = parActual.first;
            resultado[actual] = vertices[actualPadre];

            // Adiciona aristas disponibles
            typename std::list< std::pair<int,T> >::iterator itList = aristas[actual].begin();
            for (; itList != aristas[actual].end(); itList++) {
                std::pair<int,T> vertDes = *itList;
                std::pair<int, std::pair<int, T> > parN = std::make_pair(actual, vertDes);
                aristasDisponibles.push_back(parN);
            }

            // Organiza la lista por costo y si son iguales entonces se decide por cual T es menor
            aristasDisponibles.sort(
                    [](std::pair<int, std::pair<int, T> > &a, std::pair<int, std::pair<int, T> > &b) {
                        if (a.second.first == b.second.first) {
                            return a.second.second < b.second.second;
                        } else {
                            return a.second.first < b.second.first;
                        }
                    }
            );

        }
    }

    std::cout << std::endl;

    return resultado;
}

template <class T>
std::vector<T> Graph<T>::Dijkstra(T vert) {
    // Lista de predecesores para poder luego hacer caminos
    std::vector<T> resultado;
    resultado.resize(cantVertices(), T());
    std::vector<bool> visitados;
    std::vector<int> costos;

    int i_vert = buscarVertice(vert);

    if (i_vert == -1) {
        return resultado;
    }

    visitados.resize(cantVertices(), false);
    costos.resize(cantVertices(), INT_MAX);

    resultado[i_vert] = vertices[i_vert];
    costos[i_vert] = 0;

    // Cola de pares <Padre, <costo, destino> > ordenada por costo
    std::queue< std::pair<int, std::pair<int, T> > > aristasDisponibles;
    std::pair<int, T> par = std::make_pair(0, vert);
    std::pair<int, std::pair<int, T> > par2 = std::make_pair(i_vert, par);
    aristasDisponibles.push(par2);

    while(!aristasDisponibles.empty()) {
        std::pair<int, std::pair<int, T> > parActual = aristasDisponibles.front();
        aristasDisponibles.pop();

        T actualT = parActual.second.second;
        int actual = buscarVertice(actualT);
        int costoActual = costos[actual];

        int costoArista = parActual.second.first;
        int costoPadre = costos[parActual.first];
        int costoTotal = costoArista + costoPadre;

        if(costoTotal < costoActual) {
            costos[actual] = costoTotal;
            resultado[actual] = vertices[parActual.first];
        }

        if (aristasDisponibles.empty()) {
            int min = INT_MAX;
            int minInd = -1;

            for (int i = 0; i < costos.size(); ++i) {
                if (costos[i] < min && !visitados[i]) {
                    min = costos[i];
                    minInd = i;
                }
            }

            if (minInd != -1) {
                visitados[minInd] = true;
                std::cout << vertices[minInd] << " ";
                // Adiciona las aristas del vertice actual
                typename std::list< std::pair<int,T> >::iterator itList = aristas[minInd].begin();
                for (; itList != aristas[minInd].end(); itList++) {
                    std::pair<int,T> vertDes = *itList;
                    std::pair<int, std::pair<int, T> > parN = std::make_pair(minInd, vertDes);
                    aristasDisponibles.push(parN);
                }
            }
        }
    }
    std::cout << std::endl;

    return resultado;
}

// Connections
