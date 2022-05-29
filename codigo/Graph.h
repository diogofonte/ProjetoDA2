#ifndef PROJETODA2_GRAPH_H
#define PROJETODA2_GRAPH_H

#include <list>
#include <vector>

using namespace std;

//TODO passar documentacao para doxygen

class Graph {
    struct Edge {
        int origem; // Origin node
        int destino;   // Destination node
        int capacidade; // An integer weight
        int duracao;
    };

    struct Node {
        int num;
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // Has the node been visited on a search?
        /**
         * Atributo de auxílio ao algoritmo de Djikstra e ao Bfs:
         * paragem predecedente da paragem em questão no percurso a ser considerado.
         */
        int pred;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    int t;
    vector<Node> paragens; // The list of nodes being represented

public:
    Graph();
    Graph(int nodes, int edges);
    list<Edge> getAdjNodes();
    vector<int> getParagens();
    void addParagem(int n);
    void addEdge(int src, int dest, int capacidade, int duracao);
    void dfs(int v);
    void bfs(int v);
    /**
     * Complexidade temporal: O(E*log(n))\n
     * E: número total de edges que o grafo possui.\n
     * n: Tamanho/Número de nós do grafo.\n
     *
     * Determina, com recurso ao algoritmo de dijkstra, qual o caminho entre dois locais (partida e destino) percorre menor distância.
     * @param latitude1 latitude do local de partida.
     * @param longitude1 longitude do local de partida.
     * @param latitude2 latitude do destino.
     * @param longitude2 longitude do destino.
     *
     */
    void getShortestPathChangingLines(int origem, int destino, int capacidade);
};

#endif //PROJETODA2_GRAPH_H
