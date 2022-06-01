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
        int dist = 0;
        int pred = 0;
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
    /**
     * Verifica o tamanho do grafo
     * @return tamanho do grafo
     */
    int getSize() const {return (int)paragens.size();}
    /**
     * Verifica se um nó tem nós adjacentes
     * @param num nó a verificar
     * @return 1 se num não tiver nós adjacentes e 0 caso contrário
     */
    int isEmpty(int num) const {return paragens[num].adj.empty();}
    /**
     * Adiciona uma aresta ao grafo
     * @param src nó de origem da aresta
     * @param dest nó de destino da aresta
     * @param capacidade capacidade da aresta
     * @param duracao duração da aresta
     */
    void addEdge(int src, int dest, int capacidade, int duracao);
    void print();
    /**
     * Função para escrever um caminho entre src e dest
     * @param src nó de destino
     * @param dest nó de origem
     */
    void printPath(int src, int dest);//ESTA FUNÇÃO ESTÁ POR IMPLEMENTAR, FAZ SENTIDO SENDO QUE TEMO AS FUNÇOES OUTPUT EM BAIXO?
    void dfs(int v);
    void bfs(int v);
    /**
     * Determina qual o caminho entre dois locais (src e dest) que minimiza o número de transbordos.
     * @param src nó de src
     * @param dest nó de dest
     * @return capacidade do grupo
     */
    int minimizarTransbordos(int src, int dest);
    /** TODO: Apagar complexidade dps do ppt
     * Complexidade temporal: O(E*log(n))\n
     * E: número total de edges que o grafo possui.\n
     * n: Tamanho/Número de nós do grafo.\n
     *
     * Determina, com recurso ao algoritmo de dijkstra, qual o caminho entre dois locais (src e dest)
     * que maximiza a dimensão do grupo.
     * @param src é o nó de partida.
     * @param dest é o nó de chegada.
     * @return capacidade máxima do grupo
     */
    int maximizarDimensaoGrupo(int src, int dest);
    /**
     * Escreve o caminho gerado para maximizar a capacidade do grupo
     * @param src nó de origem
     * @param dest nó de destino
     * @return lista com os nós constituintes do caminho
     */
    list<int> outputCaminhoMaxC(int src, int dest);
    /**
     * Escreve o caminho gerado para minimizar o número de transbordos
     * @param src nó de origem
     * @param dest nó de destino
     * @return lista com os nós constituintes do caminho
     */
    list<int> outputCaminhoMinT(int src, int dest);
};

class Graph2 {
    private:
        vector<vector<int>> adjMx;
    public:
        Graph2(int size);
        void addParagem(int origem, int destino, int capacidade);
        int bfs(int origem, int destino, vector<int>& pai, vector<vector<int>>& gRes);
        /**
         * Determina qual o caminho entre dois locais (src e dest)
         * que maximiza a dimensão de um grupo que pode ser separado.
         * @param src nó de origem
         * @param dest nó de destino
         * @param caminho caminho pretendido para a viagem
         * @return dimensão máxima do grupo
         */
        int maximizarDimensaoGrupoSeparado(int src, int dest, vector<int> &caminho);
};

#endif //PROJETODA2_GRAPH_H
