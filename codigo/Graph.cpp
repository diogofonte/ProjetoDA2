#include "Graph.h"
#include "MaxHeap.h"

#include <iostream>
#include <queue>

Graph::Graph() {}

// Constructor: nr paragens and direction (default: undirected)
Graph::Graph(int n, int t) {
    this->n = n;
    this->t = t;
}

vector<int> Graph::getParagens() {
    vector<int> paragens;
    for (Node n: this->paragens)
        paragens.push_back(n.num);
    return paragens;
}

void Graph::addParagem(int n) {
    Node paragem;
    paragem.num = n;
    paragens.push_back(paragem);
}

// Add edge from source to destination with a certain capacity and duration
void Graph::addEdge(int src, int dest, int capacidade, int duracao) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    paragens[src].adj.push_back({dest, capacidade, duracao});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    paragens[v].visited = true;
    for (auto e : paragens[v].adj) {
        int w = e.destino;
        if (!paragens[w].visited)
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) paragens[v].visited = false;
    queue<int> q; // queue of unvisited paragens
    q.push(v);
    paragens[v]. visited = true;
    while (!q.empty()) { // while there are still unvisited paragens
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : paragens[u].adj) {
            int w = e.destino;
            if (!paragens[w].visited) {
                q.push(w);
                paragens[w].visited = true;
            }
        }
    }
}

void Graph::getShortestPathChangingLines(int origem, int destino, int capacidade) {
    int pais[paragens.size()];
    int capacidades[paragens.size()];
    for(int i = 0; i < paragens.size(); i++) {
        pais[i] = NULL;
        capacidades[i] = 0;
    }

    capacidades[origem] = INT_MAX;

    MaxHeap<int, int> paragensVisitadas(paragens.size(), 0);

    while(paragensVisitadas.getSize() > 0) {
        int v = paragensVisitadas.removeMax();

        for(auto w: paragens[v].adj) {
            if(min(capacidades[v], w.capacidade) > capacidades[w.destino]) {
                capacidades[w.destino] = min(capacidades[v], w.capacidade);
                pais[w.destino] = v;
                paragensVisitadas.increaseKey(w.destino, capacidades[w.destino]);
            }
        }
    }

    vector<int> caminho;
    int pai = paragens[destino].pred;
    while(pai != origem) {
        caminho.insert(caminho.begin(), destino);
        pai = paragens[pai].pred;
    }

    for(int i=0; i<caminho.size(); i++)
        cout << caminho[i] << " ";
}