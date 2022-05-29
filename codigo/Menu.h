#ifndef PROJETODA2_MENU_H
#define PROJETODA2_MENU_H

#include <stack>
#include <iostream>

#include "LoadData.h"
#include "Graph.h"

class Menu {
private:
    Graph grafo;
    stack<int> lastMenu;
    int option;
public:
    Menu();
    /**
     * Função para ler a opção de operação que pretende realizar
     *
     * @param minOption é o limite inferior das opções disponibilizadas
     * @param maxOption é o limite superior das opções disponibilizadas
     */
    void readOption(const unsigned& minOption, const unsigned& maxOption);
    /**
     * Função para processar o menu escolhido
     */
    void processOption();
    /**
     * Executa o menu inicial
     */
    void menu0();
    /**
     * Executa o cenário 1
     */
    void menu1();
    /**
     * Executa o cenário 2
     */
    void menu2();

};

#endif //PROJETODA2_MENU_H
