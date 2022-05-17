#ifndef FEUP_DA_AGENCIADEVIAGENS_VEICULO_H
#define FEUP_DA_AGENCIADEVIAGENS_VEICULO_H

#include "Escritorio.h"
#include <list>

using namespace std;

class Veiculo {
private:
    /**
     * origem da viagem do veículo
     */
    int origem;
    /**
     * destino da viagem do veículo
     */
    int destino;
    /**
     * valor do custo do bilhete por passageiro
     */
    int custoBilhete;
    /**
     * capacidade de passageiros total do veículo
     */
    int capacidade;
    /**
     * tempo total da viagem do veículo (ponto de origem até ao seu destino)
     */
    int tempoViagem;
    /**
     * Lista com os passageiros do veículo
     */
    List<Passageiro> passageiros;
public:
    Veiculo(int o, int d, int cB, int c, int tV, List<Passageiro> p);
    /**
     *
     * @return origem da viagem do veículo
     */
    int getOrigem() const;
    /**
     *
     * @return destino da viagem do veículo
     */
    int getDestino() const;
    /**
     *
     * @return valor do custo do bilhete por passageiro
     */
    int getCustoBilhete() const;
    /**
     *
     * @return capacidade de passageiros total do veículo
     */
    int getCapacidade() const;
    /**
     *
     * @return tempo total da viagem do veículo (ponto de origem até ao seu destino)
     */
    int getTempoViagem() const;
    /**
     * Acrescenta um novo passageiro à respetiva lista
     * @param e é o novo passageiro
     */
    bool addPassageiro(const Encomenda &e);
    /**
     * Função para comparar veículos
     *
     * @param e é o veículo a comparar
     * @return true se this == v, false se this != v
     */
    bool operator == (const Veiculo &v) const;
};

#endif //FEUP_DA_AGENCIADEVIAGENS_VEICULO_H
