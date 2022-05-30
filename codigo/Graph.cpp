#include "Graph.h"
#include "MaxHeap.h"

#include <iostream>
#include <queue>
#include <climits>

Graph::Graph() {}

// Constructor: nr paragens and direction (default: undirected)
Graph::Graph(int n) : n(n), paragens(vector<Node>(n+1, {0,0,0})) {

}

void Graph::print(){
    for(int i=0; i<paragens.size(); i++){
        printf("%d:{", i);
        for(auto it = paragens[i].adj.begin(); it != paragens[i].adj.end(); it++){
            if(std::next(it) == paragens[i].adj.end()) printf("%d", it->destino);
            else printf("%d,", it->destino);
        }
        printf("}\n");
    }
}

void Graph::addParagem(int num){
    Node paragem;
    paragem.pai = 0;
    paragem.visited = false;
    paragem.adj = list<Edge>();
    paragens[num]=paragem;
}

// Add edge from source to destinoination with a certain capacity and duration
void Graph::addEdge(int src, int destino, int capacidade, int duracao) {
    if (src<1 || src>n || destino<1 || destino>n) return;
    paragens[src].adj.push_back({destino, capacidade, duracao});
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

int Graph::maximizarDimensaoGrupo(int origem, int destino) {
    MaxHeap<int, int> visitas(n, -1);
    paragens[origem].capacidade = INT_MAX;

    int i = 1;
    for(auto p: paragens) {
        visitas.insert(i, p.capacidade);
        i++;
    }

    while(visitas.getSize() > 0) {
        int v = visitas.removeMax();
        for(auto a: paragens[v].adj) {
            int w = a.destino;
            if(min(paragens[v].capacidade, a.capacidade) > paragens[w].capacidade) {
                paragens[w].pai = v;
                paragens[w].capacidade = min(paragens[v].capacidade, a.capacidade);
                visitas.increaseKey(w, paragens[w].capacidade);
            }
        }
    }
    return paragens[destino].capacidade;
}