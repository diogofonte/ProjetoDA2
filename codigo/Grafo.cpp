#include "Grafo.h"
#include "MinHeap.h"
#include <iostream>
#include <queue>
#include <climits>

#include <chrono>

Grafo::Grafo() {}

Grafo::Grafo(int n) : n(n),
                      paragens(vector<Node>(n + 1, {0, 0, 0})) {

}

void Grafo::print(){
    for(int i=0; i<paragens.size(); i++){
        cout << i << ":{";
        for(auto it = paragens[i].adj.begin(); it != paragens[i].adj.end(); it++){
            if(std::next(it) == paragens[i].adj.end()) cout << it->destino;
            else cout << it->destino << ", ";
        }
        cout << "}" << endl;
    }
}

void Grafo::addParagem(int num){
    Node paragem;
    paragem.pai = 0;
    paragem.visited = false;
    paragem.adj = list<Edge>();
    paragens[num]=paragem;
}

void Grafo::addAresta(int src, int dest, int capacidade, int duracao) {
    if (src<1 || src>n || dest < 1 || dest > n) return;
    paragens[src].adj.push_back({dest, capacidade, duracao});
}

void Grafo::dfs(int id) {
    cout << id << " ";
    paragens[id].visited = true;
    for (auto e : paragens[id].adj) {
        int w = e.destino;
        if (!paragens[w].visited)
            dfs(w);
    }
}

void Grafo::bfs(int id) {
    for (int v=1; v<=n; v++) paragens[v].visited = false;
    queue<int> unvisited;
    unvisited.push(id);
    paragens[id]. visited = true;
    while (!unvisited.empty()) {
        int nodeOrder = unvisited.front(); unvisited.pop();
        cout << nodeOrder << " ";
        for (auto e : paragens[nodeOrder].adj) {
            int w = e.destino;
            if (!paragens[w].visited) {
                unvisited.push(w);
                paragens[w].visited = true;
            }
        }
    }
}

int Grafo::maximizarDimensaoGrupo(int src, int dest) {
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

int Grafo::minimizarTransbordos(int src, int dest) {
    MinHeap<int, int> heap((int)paragens.size(), -1);
    for(int i = 1; i < paragens.size(); i++){
        paragens[i].dist = INT_MAX;
        paragens[i].visited = false;
        heap.insert(i, INT_MAX);
    }
    paragens[src].dist = 0;
    paragens[src].pai = src;
    heap.decreaseKey(src, 0);
    while(heap.getSize() != 0){
        int u = heap.removeMin();
        paragens[u].visited = true;
        for(auto edge : paragens[u].adj){
            int v = edge.destino;
            if(!paragens[v].visited && paragens[u].dist + edge.capacidade < paragens[v].dist) {
                int newWeight = paragens[u].dist + edge.capacidade;
                paragens[v].dist = newWeight;
                paragens[v].pai = u;
                heap.decreaseKey(v, newWeight);
            }
        }
    }
    if(paragens[dest].dist == INT_MAX) return -1;
    else return paragens[dest].dist;
}

list<int> Grafo::caminhoMaxC(int src, int dest) {
    list<int> path;
    maximizarDimensaoGrupo(src,dest);
    int u = dest;
    while(u != 0){
        path.push_back(u);
        u = paragens[u].pai;
    }
    path.reverse();
    return path;
}

list<int> Grafo::caminhoMinT(int src, int dest) {
    list<int> path;
    minimizarTransbordos(src, dest);
    path.push_front(dest);
    do{
        if(paragens[dest].pai == dest) {
            path.clear();
            break;
        }
        dest = paragens[dest].pai;
        path.push_front(dest);
    } while(dest != src);
    return path;
}

int Grafo::getDuracaoMinima(int src, int dest) {
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

int Grafo::getEsperaMaxima(int src, int dest) {
    int es = getDuracaoMinima(src, dest);
    int espera_max = INT_MIN;
    vector<int> caminho;
    vector<int> esperas(getSize()+1,0);
    for(int i = 1; i <= getSize(); i++){
        for (auto e : paragens[i].adj) {
            int max = paragens[e.destino].es - paragens[i].es - e.duracao;
            if(esperas[e.destino] < max)
                esperas[e.destino] = max;
        }
    }
    for(int e : esperas){
        if(espera_max < e)
            espera_max = e;
    }
    for(int i = 1; i <= esperas.size(); i++) {
        if (esperas[i] == espera_max) {
            caminho.push_back(i);
        }
    }
    return espera_max;
}

//-------------------- Grafo 2 -------------------------//

Grafo2::Grafo2() {}

Grafo2::Grafo2(int nodes): n(nodes), paths(list<list<int>>()), caps(list<int>()) {
    adj.resize(nodes + 1); // +1 se os nos comecam em 1 ao inves de 0
    cap.resize(nodes + 1);
    cap_safe_copy.resize(nodes + 1);
    for (int i=1; i <= nodes; i++) cap[i].resize(nodes + 1);
    for (int i=1; i <= nodes; i++) cap_safe_copy[i].resize(nodes + 1);
}

void Grafo2::addLink(int id1, int id2, int c) {
    // adjacencias do grafo nao dirigido, porque podemos ter de andar no sentido
    // contrario ao procurarmos caminhos de aumento
    adj[id1].push_back(id2);
    adj[id2].push_back(id1);
    cap[id1][id2] = c;
    cap_safe_copy[id1][id2] = c;
}

// BFS para encontrar caminho de aumento
// devolve valor do fluxo nesse caminho
int Grafo2::bfs(int src, int dest, vector<int> &parent) {
    for (int i=1; i<=n; i++) parent[i] = -1;

    parent[src] = -2;
    queue<pair<int, int>> q;           // fila do BFS com pares (no, capacidade)
    q.push({src, INT_MAX}); // inicializar com no origem e capacidade infinita

    while (!q.empty()) {
        // retirar primeiro no da fila
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        // percorrer nós adjacentes ao nó atual (cur)
        for (int next : adj[cur]) {
            // se o vizinho ainda nao foi visitado (parent==-1)
            // e a aresta respetiva ainda tem capacidade para passar fluxo
            if (parent[next] == -1 && cap[cur][next]>0) {
                parent[next] = cur;                        // atualizar pai
                int new_flow = min(flow, cap[cur][next]);  // atualizar fluxo
                if (next == dest) return new_flow;         // chegamos ao final?
                q.push({next, new_flow});       // adicionar a fila
            }
        }
    }

    return 0;
}

int Grafo2::maximizarDimensaoGrupoSeparado(int src, int dest) {
    cap = cap_safe_copy;
    paths.clear();
    caps.clear();
    int flow = 0;
    vector<int> parent(n+1);
    while (true) {
        int new_flow = bfs(src, dest, parent);
        if (new_flow == 0) break;

        list<int> path;
        path.push_back(dest);

        caps.push_back(new_flow);
        flow += new_flow;
        int cur = dest;
        while (cur != src) {
            int prev = parent[cur];
            cap[prev][cur] -= new_flow;
            cap[cur][prev] += new_flow;
            cur = prev;
            path.push_back(cur);
        }
        paths.push_back(path);
    }
    return flow;
}

bool Grafo2::encaminhamento(int src, int dest, int size) {
    int maxDimensao = maximizarDimensaoGrupoSeparado(src, dest);
    if(maxDimensao < size) return false;
    cout << "Quantidade de pessoas no caminho/capacidade máxima do caminho:" << endl;
    bool visited[caps.size()];
    int actual_size = size;
    while(actual_size > 0){
        int max=0, i=0, maxIndex=0;
        for(auto it : caps){
            if(it > max && !visited[i]){
                maxIndex = i;
                max = it;
            }
            i++;
        }
        visited[maxIndex] = true;
        actual_size-=max;
        int qntPessoas;
        if(actual_size < 0){
            qntPessoas = max + actual_size;
        }else{
            qntPessoas = max;
        }
        cout << qntPessoas << "/" << max << ": ";
        int j=0;
        for(auto it : paths){
            if(j == maxIndex){
                it.reverse();
                for (auto it2 = it.begin(); it2 != it.end(); it2++) {
                    if (next(it2) == it.end()) cout << *it2;
                    else cout << *it2 << " -> ";
                }
                cout << endl;
            }
            j++;
        }
    }
    return true;
}
