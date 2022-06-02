#ifndef PROJETODA2_LOADDATA_H
#define PROJETODA2_LOADDATA_H

#include "Grafo.h"

class LoadData {
public:
    /**
     * Carrega os dados do grafo para as estruturas de dados correspondentes
     * @param num_ficheiro número do ficheiro de input
     * @return grafo pronto a ser explorado
     */
    Grafo loadGrafo(int num_ficheiro) const;
    /**
     * Carrega os dados do grafo de tipo 2 para as estruturas de dados correspondentes
     * @param num_ficheiro número do ficheiro de input
     * @return grafo do tipo 2 pronto a ser explorado
     */
    Grafo2 loadGrafo2(int num_ficheiro) const;
};

#endif //PROJETODA2_LOADDATA_H
