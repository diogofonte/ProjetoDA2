#include "Graph.h"
#include "MaxHeap.h"
#include "MinHeap.h"

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

// Breadth-First Search: example implementation
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

int Graph::maximizarDimensaoGrupo(int src, int dest) {
    MaxHeap<int, int> visitas(n, -1);
    paragens[src].capacidade = INT_MAX;

    int i = 1;
    for(auto p: paragens) {
        visitas.insert(i, p.capacidade);
        p.capacidade = INT_MIN;
        p.pred = 0;
        i++;
    }

    while(visitas.getSize() > 0) {
        int v = visitas.removeMax();
        if(paragens[v].capacidade == INT_MIN) break;
        for(auto a: paragens[v].adj) {
            int w = min(paragens[v].capacidade, a.capacidade);
            if(w > paragens[a.destino].capacidade){
                paragens[a.destino].capacidade = w;
                paragens[a.destino].pred = v;
                visitas.increaseKey(v, w);
            }
            //int w = a.dest;
//            if(min(paragens[v].capacidade, a.capacidade) > paragens[w].capacidade) {
//                paragens[w].pai = v;
//                paragens[w].capacidade = min(paragens[v].capacidade, a.capacidade);
//                visitas.increaseKey(w, paragens[w].capacidade);
//            }
        }
    }

    return paragens[dest].capacidade;
}

int Graph::minimizarTransbordos(int src, int dest) {
    MinHeap<int, int> heap(paragens.size(), -1);
    for(int i = 1; i < paragens.size(); i++){
        paragens[i].dist = INT_MAX;
        paragens[i].visited = false;
        heap.insert(i, INT_MAX);
    }
    paragens[src].dist = 0;
    paragens[src].pred = src;
    heap.decreaseKey(src, 0);
    while(heap.getSize() != 0){
        int u = heap.removeMin();
        paragens[u].visited = true;
        for(auto edge : paragens[u].adj){
            int v = edge.destino;
            if(!paragens[v].visited && paragens[u].dist + edge.capacidade < paragens[v].dist) {
                int newWeight = paragens[u].dist + edge.capacidade;
                paragens[v].dist = newWeight;
                paragens[v].pred = u;
                heap.decreaseKey(v, newWeight);
            }
        }
    }
    if(paragens[dest].dist == INT_MAX) return -1;
    else return paragens[dest].dist;
}

list<int> Graph::outputCaminhoMaxC(int src, int dest) {
    list<int> path;
    int u = dest;
    while(u != 0){
        path.push_back(u);
        u = paragens[u].pred;
    }
    path.reverse();
    return path;
}

list<int> Graph::outputCaminhoMinT(int src, int dest) {
    list<int> path;
    minimizarTransbordos(src, dest);
    path.push_front(dest);
    do{
        if(paragens[dest].pred == dest) {
            path.clear();
            break;
        }
        dest = paragens[dest].pred;
        path.push_front(dest);
    }while(dest != src);
    return path;
}

Graph2::Graph2(int size) {
    vector<vector<int>> g(size + 1, vector<int> (size + 1, 0));
    this->adjMx = g;
}

void Graph2::addParagem(int origem, int destino, int capacidade) {
    adjMx[origem][destino] = capacidade;
}

int Graph2::bfs(int origem, int destino, vector<int>& pai, vector<vector<int>>& gRes) {
    for(int i = 0; i < pai.size(); i++) {
        if(i == origem) {
            pai[i] = -2;
            continue;
        }
        pai[i] = -1;
    }
    queue<pair<int, int>> q;
    q.push({origem, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int capacity = q.front().second;
        q.pop();
        for (int v=0; v < gRes.size(); v++) {
            if (u != v && pai[v] == -1 && gRes[u][v] != 0) {
                pai[v] = u;
                int capacidade_min = min(capacity, gRes[u][v]);
                if (v == destino)
                    return capacidade_min;
                q.push({v, capacidade_min});
            }
        }
    }
    return 0;
}

int Graph2::maximizarDimensaoGrupoSeparado(int src, int dest, vector<int> &caminho) {
    vector<int> pai(adjMx.size(), -1);

    vector<vector<int>> gRes = adjMx;

    int capacidade_min = bfs(src, dest, pai, gRes), fluxo_max = 0;
    while (capacidade_min) {
        fluxo_max += capacidade_min;
        int u = dest;
        while (u != src) {
            int v = pai[u];
            gRes[u][v] += capacidade_min;
            gRes[v][u] -= capacidade_min;
            u = v;
        }

        capacidade_min = bfs(src, dest, pai, gRes);
    }
    return fluxo_max;
}