#ifndef PROJETODA2_GRAFO_H
#define PROJETODA2_GRAFO_H

#include <list>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

//classe grafo para cenário 1
class Grafo {
    struct Edge {
        /**
         * Nó de destino
         */
        int destino = 0;
        /**
         * Capacidade da aresta (viagem)
         */
        int capacidade = 0; // An integer weight
        /**
         * Duração da aresta (viagem)
         */
        int duracao = 0;
    };

    struct Node {
        /**
         * Distância da paragem à origem do percurso
         */
        int dist = 0;
        /**
         * Nó pai deste nó (local)
         */
        int pai = 0;
        /**
         * earliest start do nó
         */
        int es = 0;
        /**
         * latest finish do nó
         */
        int lf = 0;
        /**
         * Grau do nó (local)
         */
        int grau = 0;
        /**
         * Capacidade que chega ao nó (local)
         */
        int capacidade = 0;
        /**
         * Variável para controlar se o nó (local) já foi ou não visitado numa pesquisa
         */
        bool visited = false;
        /**
         * Lista de arestas que saem do nó (local), para nós (locais) adjacentes
         */
        list<Edge> adj = {};
    };

    //atributos do grafo
    /**
     * Tamanho do nó (1 a n)
     */
    int n;
    /**
     * Lista de nós (locais) representados no grafo
     */
    vector<Node> paragens;

public:
    /**
     * Construtor por omissão de argumentos de um grafo
     */
    Grafo();
    /**
     * Construtor de um grafo com número de nós (locais)
     * @param nodes número de nós (locais) que o grafo terá
     */
    Grafo(int nodes);
    /**
     * Adiciona um nó (local) ao grafo
     * @param num identificador do novo nó (local)
     */
    void addParagem(int num);
    /**
     * Devolve o tamanho do grafo
     * @return tamanho do grafo
     */
    int getSize() const {
        return (int)paragens.size();
    }
    /**
     * Verifica se um nó (local) tem nós (locais) adjacentes
     * @param num nó (local) a verificar
     * @return 1 se num não tiver nós (locais) adjacentes e 0 caso contrário
     */
    int isEmpty(int num) const {
        return paragens[num].adj.empty();
    }
    /**
     * Adiciona uma aresta (viagem) ao grafo
     * @param src nó (local) de origem da aresta (viagem)
     * @param dest nó (local) de destino da aresta (viagem)
     * @param capacidade capacidade da aresta (viagem)
     * @param duracao duração da aresta (viagem)
     */
    void addAresta(int src, int dest, int capacidade, int duracao);
    /**
     * Imprime o grafo
     */
    void print();
    /**
     * Faz uma pesquisa do tipo Depth-First
     * @param id identificador do nó atual (local)
     */
    void dfs(int id);
    /**
     * Faz uma pesquisa do tipo Breadth-First
     * @param id identificador do nó atual (local)
     */
    void bfs(int id);
    /**
     * Determina qual o caminho entre dois locais (src e dest) que minimiza o número de transbordos.
     * @param src nó (local) de origem
     * @param dest nó (local) de destino
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
     * @param src é o nó (local) de partida.
     * @param dest é o nó (local) de chegada.
     * @return capacidade máxima do grupo
     */
    int maximizarDimensaoGrupo(int src, int dest);
    /**
     * Escreve o caminho gerado para maximizar a capacidade do grupo
     * @param dest nó (local) de destino
     * @return lista com os nós (locais) constituintes do caminho
     */
    list<int> outputCaminhoMaxC(int dest);
    /**
     * Escreve o caminho gerado para minimizar o número de transbordos
     * @param src nó (local) de origem
     * @param dest nó (local) de destino
     * @return lista com os nós (locais) constituintes do caminho
     */
    list<int> outputCaminhoMinT(int src, int dest);
    /**
     * Determina a duração miníma da viagem entre os locais src e dest
     * @param src nó (local) de origem
     * @param dest nó (local) de destino
     * @return duração miníma da viagem entre os dois locais
     */
    int getDuracaoMinima(int src, int dest);
};

//classe grafo para cenário 2
class Grafo2 {
    private:
        /**
         * Número de nós (locais) do grafo
         */
        int n;
        /**
         * Lista de adjacências do grafo
         */
        vector<vector <int>> adj;
        /**
         * Matriz de capacidades do grafo
         */
        vector<vector <int>> cap;
        /**
         * Lista de caminhos do grafo
         */
        list<list<int>> paths;
    public:
        /**
         * Contrutor por omissão de argumentos de um grafo
         */
        Grafo2();
        /**
         * Contrutor de um grafo com número de nós (locais)
         * @param nodes número de nós (locais) que o grafo terá
         */
        Grafo2(int nodes);
        /**
         * Adiciona adjacência do grafo dirigido
         * para podermos andar no sentido contrario quando procuramos caminhos de aumento
         * @param a identificador do primeiro nó (local)
         * @param b identificador do segundo nó (local)
         * @param c capacidade da ligação
         */
        void addLink(int a, int b, int c);
        /**
         * Pesquisa Breadth-First para encontrar caminho de aumento
         * @param src nó (local) de origem
         * @param dest nó (local) de destino
         * @param parent lista com o identificador do nó (local) pai de cada nó (local) i
         * @return valor do fluxo no caminho
         */
        int bfs(int src, int dest, vector<int> &parent);
        /**
         * Determina qual o caminho entre dois locais (src e dest)
         * que maximiza a dimensão de um grupo que pode ser separado.
         * @param src nó de origem
         * @param dest nó de destino
         * @param caminho caminho pretendido para a viagem
         * @return dimensão máxima do grupo
         */
        int maximizarDimensaoGrupoSeparado(int src, int dest);
        /**
         * Devolve a lista dos caminhos do grafo
         * @return lista de caminhos encontrados
         */
        list<list<int>> outputCaminhoMaxC(){
            return paths;
        }
};

#endif //PROJETODA2_GRAFO_H
