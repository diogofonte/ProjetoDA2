#ifndef FEUP_DA_AGENCIADEVIAGENS_LOADDATA_H
#define FEUP_DA_AGENCIADEVIAGENS_LOADDATA_H

#include "Escritorio.h"

class LoadData {
public:
    /**
     * Função para carregar todos os dados de um escritório
     *
     * @param a é o escritório para onde vão ser carregados os dados
     */
    LoadData(Escritorio &a, int percentagem);
    /**
     * Função para carregar os dados de um escritório
     *
     * @param a é o escritório
     */
    void loadEstafetas(Escritorio &a, int numEstafetas);
    /**
     * Função para carregar os dados de um escritório
     *
     * @param a é o escritório
     */
    void loadEncomendas(Escritorio &a, int numEncomendas);
};

#endif //FEUP_DA_AGENCIADEVIAGENS_LOADDATA_H
