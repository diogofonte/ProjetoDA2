#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <climits>

using namespace std;

#include "Escritorio.h"
#include "LoadData.h"

LoadData::LoadData(Escritorio &a, int percentagem) {
    loadEstafetas(a, percentagem);
    loadEncomendas(a, percentagem);
}

void LoadData::loadEstafetas(Escritorio &a, int percentagem) {
    ifstream f;
    string info;
    double volMax;
    double pesoMax;
    double custo;
    string v, p, c;

    f.open("carrinhas"+to_string(percentagem)+".txt");

    if (!f.is_open()) {
        cout << "Ficheiro nao existe." << endl;
        exit(0);
    }

    f.ignore(LONG_MAX, '\n');
    while (getline(f, info)) {
        stringstream s(info);
        getline (s, v, ' ');
        getline (s, p, ' ');
        getline (s, c, ' ');

        volMax = stoi(v);
        pesoMax = stoi(p);
        custo = stoi(c);

        //a.addEstafeta(Estafeta(volMax, pesoMax, custo, 0.0, 0.0, list<Encomenda>()));
    }
    f.close();
}

void LoadData::loadEncomendas(Escritorio &a, int percentagem) {
    ifstream f;
    string info;
    double volume, peso, recompensa, duracao;
    string v, p, r, d;

    f.open("encomendas"+to_string(percentagem)+".txt");

    if (!f.is_open()) {
        cout << "Ficheiro nao existe." << endl;
        exit(0);
    }

    f.ignore(LONG_MAX, '\n');
    while (getline(f, info)) {
        stringstream s(info);
        getline (s, v, ' ');
        getline (s, p, ' ');
        getline (s, r, ' ');
        getline (s, d, ' ');

        volume = stoi(v);
        peso = stoi(p);
        recompensa = stoi(r);
        duracao = stoi(d);

        //a.addEncomenda(Encomenda(volume, peso, recompensa, duracao));
    }

    f.close();
}