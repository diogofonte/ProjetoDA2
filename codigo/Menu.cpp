#include <iomanip>
#include "Menu.h"

Menu::Menu() {
    cout << "AGÊNCIA DE VIAGENS" << endl;

    option = 0;
    grafo = Grafo(0);
    grafo2 = Grafo2(0);

    int num_ficheiro;
    cout << "Insira o número do ficheiro do dataset a usar: ";
    cin >> num_ficheiro;
    cout << endl;

    LoadData loadData;
    this->grafo = loadData.loadGrafo(num_ficheiro);
    this->grafo2 = loadData.loadGrafo2(num_ficheiro);

    lastMenu.push(0);   //'0' representa o menu inicial/principal
    menu0(num_ficheiro);
}

void Menu::readOption(const unsigned& minOption, const unsigned& maxOption) {
    bool validOption;
    do {
        cin >> option;
        if (cin.fail()) {
            if (cin.eof()) {
                cout << "OPERAÇÃO TERMINADA COM SUCESSO." << endl;
                exit (1);
            }
            else {
                validOption = false;
                cout << "OPÇÃO INVÁLIDA! TENTE NOVAMENTE" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
        else if ((minOption <= option &&  option <= maxOption) || option == 0) {
            validOption = true;
            cin.ignore(1000, '\n');
        }
        else {  // O utilizador introduziu um inteiro invalido
            validOption = false;
            cout << "OPÇÃO INVÁLIDA! TENTE NOVAMENTE. " << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!validOption);
}

void Menu::processOption(int num_ficheiro) {
    switch (option) {
        case 0: menu0(num_ficheiro);
            break;
        case 1: menu1(num_ficheiro);
            break;
        case 2: menu2(num_ficheiro);
            break;
    }
}

void Menu::menu0(int num_ficheiro) {
    cout << "1. Grupos que não se separam" << endl; // cenario 1
    cout << "2. Grupos que se podem separar" << endl; // cenario 2
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 2);

    if (option) {
        lastMenu.push(0);
        processOption(num_ficheiro);
    }
    else {
        cout << "OPERAÇÃO TERMINADA COM SUCESSO";
        exit (0);
    }
}

void Menu::executeOne1(int origem, int destino){
    int capacidade = grafo.maximizarDimensaoGrupo(origem, destino);
    if(capacidade == 0) cout << "Percurso não disponível!" << endl;
    else{
        cout << "Para o percurso selecionado, a dimensão máxima do grupo é de " << capacidade << " pessoas." << endl
             << "O caminho encontrado foi o seguinte: ";
        //grafo.test(destino, destino);
        list<int> caminho = grafo.outputCaminhoMaxC(destino);
        for(auto it = caminho.begin(); it != caminho.end(); it++){
            if(next(it) == caminho.end()) printf("%d\n", *it);
            else printf("%d -> ", *it);
        }
    }

}

void Menu::executeOne2(int origem, int destino){
    //mostrar caminho que maximiza a dimensão
    printf("Caminho com maior capacidade: ");
    list<int> caminho = grafo.outputCaminhoMaxC(destino);
    for(auto it = caminho.begin(); it != caminho.end(); it++){
        if(next(it) == caminho.end()) printf("%d\n", *it);
        else printf("%d -> ", *it);
    }

    //mostrar caminho que minimiza os transbordos
    printf("Caminho com menos transbordos: ");
    list<int> caminho2 = grafo.outputCaminhoMinT(origem, destino);
    for (auto it = caminho2.begin(); it!=caminho2.end(); it++) {
       if(next(it) == caminho2.end()) cout << *it;
       else cout << *it << " -> ";
    }
    cout << endl;
}

void Menu::menu1(int num_ficheiro) {
    cout << "1. Caminho que maximiza a dimensão do grupo" << endl;
    cout << "2. Caminho que maximiza a dimensão do grupo e Caminho que minimiza o número de transbordos" << endl;
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 2);

    int origem, destino;
    cout << "Insira um ponto de partida válido: ";
    cin >> origem;
    cout << endl;
    cout << "Insira um destino válido: ";
    cin >> destino;
    cout << endl;

    switch(option) {
        case 1:
            executeOne1(origem, destino);
            break;
        case 2:
            executeOne2(origem, destino);
            break;
    }

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(num_ficheiro);
}

//----------------------------------------------------------------------------------------------------------------------

void Menu::executeTwo1(int num_ficheiro, int origem, int destino){

}

void Menu::executeTwo2(int num_ficheiro, int origem, int destino){

}

void Menu::executeTwo3(int num_ficheiro, int origem, int destino){
    int capacidade = grafo2.maximizarDimensaoGrupoSeparado(origem, destino);
    if(capacidade == 0) cout << "Percurso não disponível!" << endl;
    else {
        cout << "Para o percurso selecionado, a dimensão máxima do grupo é de " << capacidade << " pessoas." << endl;
        list<list<int>> caminhos = grafo2.outputCaminhoMaxC();
        for (auto caminho: caminhos) {
            caminho.reverse();
            for (auto it = caminho.begin(); it != caminho.end(); it++) {
                if (next(it) == caminho.end()) cout << *it;
                else cout << *it << " -> ";
            }
            printf("\n");
        }
    }
}

void Menu::executeTwo4(int num_ficheiro, int origem, int destino){

}

void Menu::executeTwo5(int num_ficheiro, int origem, int destino){

}

void Menu::menu2(int num_ficheiro) {
    cout << "1. Caminho para um grupo, dada uma dimensão" << endl;
    cout << "2. Corrigir caminho, se necessário, para que a dimensão de um grupo possa aumentar em um número de unidades dadas" << endl;
    cout << "3. Dimensão máxima e caminho que maximiza a dimensão do grupo" << endl;
    cout << "4. Determinar quando é que o grupo se reuniria novamente, partindo de um caminho que constitui um grafo acíclico" << endl;
    cout << "5. Indicar o tempo máximo de espera e os locais em que alguns elementos esperam pelos colegas de grupo" << endl;
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 5);

    int origem, destino;
    cout << "Insira um ponto de partida válido: ";
    cin >> origem;
    cout << "Insira um destino válido: ";
    cin >> destino;

    switch(option) {
        case 1:
            executeTwo1(num_ficheiro, origem, destino);
            break;
        case 2:
            executeTwo2(num_ficheiro, origem, destino);
            break;
        case 3:
            executeTwo3(num_ficheiro, origem, destino);
            break;
        case 4:
            executeTwo4(num_ficheiro, origem, destino);
            break;
        case 5:
            executeTwo5(num_ficheiro, origem, destino);
            break;
    }

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(num_ficheiro);
}
