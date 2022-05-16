#include <iomanip>
#include "Menu.h"

Menu::Menu(): option(0){
    int percentagem;

    cout << "Agência de Viagens" << endl;

    cout << "Insira a percentagem do dataset a usar (25, 50, 75, 100): ";
    cin >> percentagem;
    cout << endl;

    LoadData loadData(a, percentagem);

    lastMenu.push(0);   //'0' representa o menu inicial/principal
    menu0();
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

void Menu::processOption() {
    switch (option) {
        case 0: menu0();
            break;
        case 1: menu1();
            break;
        case 2: menu2();
            break;
    }
}

void Menu::menu0() {
    cout << "1. Grupos que não se separam" << endl; // cenario 1
    cout << "2. Grupos que se podem separar" << endl; // cenario 2
    cout << "0. Sair." << endl;
    cout << "\nESCOLHA UMA OPÇÃO:";
    readOption(0, 2);

    if (option) {
        lastMenu.push(0);
        processOption();
    }
    else {
        cout << "OPERAÇÃO TERMINADA COM SUCESSO";
        exit (0);
    }
}

void Menu::menu1() {
    //2 alíneas

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}

void Menu::menu2() {
    //5 alíneas

    cout << endl;
    option = lastMenu.top();
    lastMenu.pop();
    processOption();
}