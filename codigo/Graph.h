#ifndef PROJETODA2_GRAPH_H
#define PROJETODA2_GRAPH_H

#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//TODO passar documentacao para doxygen

class Graph {
    struct Edge {
        int destino=0;   // Destination node
        int capacidade=0; // An integer weight
        int duracao=0;
    };

    struct Node {
        int pai=0;
        int capacidade=0;
        bool visited=false;   // Has the node been visited on a search?
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> paragens; // The list of nodes being represented

public:
    Graph();
    Graph(int nodes);
    void addParagem(int num);
    list<Edge> getAdjNodes();
    int getSize() const {return (int)paragens.size();}
    int isEmpty(int num) const {return paragens[num].adj.empty();}
    void addEdge(int src, int dest, int capacidade, int duracao);
    void print();
    void dfs(int v);
    void bfs(int v);
    /** TODO: Apagar complexidade dps do ppt
     * Complexidade temporal: O(E*log(n))\n
     * E: número total de edges que o grafo possui.\n
     * n: Tamanho/Número de nós do grafo.\n
     *
     * Determina, com recurso ao algoritmo de dijkstra, qual o caminho entre dois locais (origem e destino)
     * que maximiza a dimensão do grupo.
     * @param origem é o nó de partida.
     * @param destino é o nó de chegada.
     *
     */
    int maximizarDimensaoGrupo(int origem, int destino);
};

#endif //PROJETODA2_GRAPH_H
