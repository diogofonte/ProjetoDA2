#include "Graph.h"
#include "MaxHeap.h"
#include "MinHeap.h"

#include <iostream>
#include <queue>
#include <climits>
#include <bits/stdc++.h>

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
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>container;
        container.push(make_pair(0, src));

        for(auto it : paragens){
            it.capacidade = INT_MIN;
            it.pai = 0;
        }
        paragens[src].capacidade = INT_MAX;

        while (!container.empty()) {
            pair<int, int> temp = container.top();
            int current_src = temp.second;
            container.pop();
              for(auto vertex : paragens[current_src].adj){
                int distance = max(paragens[vertex.destino].capacidade, min(paragens[current_src].capacidade, vertex.capacidade));
                if(distance > paragens[vertex.destino].capacidade){
                    paragens[vertex.destino].capacidade = distance;
                    paragens[vertex.destino].pai = current_src;
                    container.push(make_pair(distance, vertex.destino));
                }
            }
        }
        return paragens[dest].capacidade;
}

int Graph::minimizarTransbordos(int src, int dest) {
    MinHeap<int, int> heap((int)paragens.size(), -1);
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

list<int> Graph::outputCaminhoMaxC(int dest) {
    list<int> path;
    int u = dest;
    while(u != 0){
        path.push_back(u);
        u = paragens[u].pai;
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

Graph2::Graph2(int n): n(n), paths(list<list<int>>()) {
    adj.resize(n+1); // +1 se os nos comecam em 1 ao inves de 0
    cap.resize(n+1);
    for (int i=1; i<=n; i++) cap[i].resize(n+1);
}

void Graph2::addLink(int a, int b, int c) {
    // adjacencias do grafo nao dirigido, porque podemos ter de andar no sentido
    // contrario ao procurarmos caminhos de aumento
    adj[a].push_back(b);
    adj[b].push_back(a);
    cap[a][b] = c;
}

// BFS para encontrar caminho de aumento
// devolve valor do fluxo nesse caminho
int Graph2::bfs(int src, int dest, vector<int> &parent) {
    for (int i=1; i<=n; i++) parent[i] = -1;

    parent[src] = -2;
    queue<pair<int, int>> q; // fila do BFS com pares (no, capacidade)
    q.push({src, INT_MAX});    // inicializar com no origem e capacidade infinita

    while (!q.empty()) {
        // returar primeiro no da fila
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        // percorrer nos adjacentes ao no atual (cur)
        for (int next : adj[cur]) {
            // se o vizinho ainda nao foi visitado (parent==-1)
            // e a aresta respetiva ainda tem capacidade para passar fluxo
            if (parent[next] == -1 && cap[cur][next]>0) {
                parent[next] = cur;                        // atualizar pai
                int new_flow = min(flow, cap[cur][next]);  // atualizar fluxo
                if (next == dest) return new_flow;            // chegamos ao final?
                q.push({next, new_flow});                  // adicionar a fila
            }
        }
    }

    return 0;
}

// Algoritmo de Edmonds-Karp para fluxo maximo entre s e t
// devolve valor do fluxo maximo (cap[][] fica com grafo residual)
int Graph2::maximizarDimensaoGrupoSeparado(int src, int dest) {
    int flow = 0;             // fluxo a calcular
    vector<int> parent(n+1);  // vetor de pais (permite reconstruir caminho)
    while (true) {
        int new_flow = bfs(src, dest, parent); // fluxo de um caminho de aumento
        if (new_flow == 0) break;         // se nao existir, terminar

        list<int> path;
        // imprimir fluxo e caminho de aumento
        //cout << "Caminho de aumento: fluxo " << new_flow << " | " << dest;
        path.push_back(dest);

        flow += new_flow;  // aumentar fluxo total com fluxo deste caminho
        int cur = dest;
        while (cur != src) { // percorrer caminho de aumento e alterar arestas
            int prev = parent[cur];
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
            //cout << " <- " << cur; // imprimir proximo no do caminho
            path.push_back(cur);
        }
        //cout << endl;
        paths.push_back(path);
    }
    return flow;
}

Graph2::Graph2() {}

int Graph::getDuracaoMinima(int origem, int destino) {
    for (auto p: paragens) {
        p.es = 0;
        p.pai = 0;
        p.grau = 0;
    }

    for (auto p: paragens) {
        for (auto e: p.adj) {
            paragens[e.destino].grau += 1;
        }
    }

    queue<int> s;
    int dur_min = -1, vf = 0;
    for (int i = 0; i < paragens.size(); i++)
        if (paragens[i].grau == 0)
            s.push(i);

    while (s.size() > 0) {
        int v = s.front();
        s.pop();
        if (dur_min < paragens[v].es) {
            dur_min = paragens[v].es;
            vf = v;
        }
        for (auto w: paragens[v].adj) {
            if (paragens[w.destino].es < paragens[v].es + w.duracao) {
                paragens[w.destino].es = paragens[v].es + w.duracao;
                paragens[w.destino].pai = v;
            }
            paragens[w.destino].grau -= 1;
            if (paragens[w.destino].grau == 0)
                s.push(w.destino);
        }
    }

    return dur_min;
}