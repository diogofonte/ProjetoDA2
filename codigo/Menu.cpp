#include <iomanip>
#include "Menu.h"

Menu::Menu() {
    cout << "AGÊNCIA DE VIAGENS" << endl;

    option = 0;
    grafo = Graph(0);

    int num_ficheiro;
    cout << "Insira o número do ficheiro do dataset a usar: ";
    cin >> num_ficheiro;
    cout << endl;

    LoadData loadData;
    this->grafo = loadData.loadGrafo(num_ficheiro);

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

void Menu::menu1(int num_ficheiro) {
    cout << "3. Caminho que maximiza a dimensão do grupo" << endl;
    cout << "4. " << endl;
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 4);
    //grafo.print();

    int origem, destino;
    cout << "Insira um ponto de partida válido: ";
    cin >> origem;
    cout << endl;
    cout << "Insira um destino válido: ";
    cin >> destino;
    cout << endl;

    switch(option) {
        case 3:
            int capacidade = grafo.maximizarDimensaoGrupo(origem, destino);
            if(capacidade == 0) cout << "Percurso não disponível!" << endl;
            else cout << "Para o percurso selecionado, a dimensão máxima do grupo é de " << capacidade << " pessoas." << endl;
    }


    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(num_ficheiro);
}


void Menu::menu2(int num_ficheiro) {
    cout << "5. Caminho dada uma dimensão para o grupo" << endl;
    cout << "6. " << endl;
    cout << "7. Caminho que maximiza a dimensão do grupo" << endl;
    cout << "8. " << endl;
    cout << "9. " << endl;
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 9);
    //grafo.print();

    int origem, destino;
    cout << "Insira um ponto de partida válido: ";
    cin >> origem;
    cout << "Insira um destino válido: ";
    cin >> destino;

    switch(option) {
        case 7:
            LoadData loadData;
            Graph2 adjMx = loadData.loadGrafo2(num_ficheiro);
            int capacidade = adjMx.maximizarDimensaoGrupoSeparado(origem, destino);
            if(capacidade == 0) cout << "Percurso não disponível!" << endl;
            else cout << "Para o percurso selecionado, a dimensão máxima do grupo é de " << capacidade << " pessoas." << endl;
    }
    //grafo.print();


    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption(num_ficheiro);
}