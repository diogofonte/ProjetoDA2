#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

#include "LoadData.h"
#include "Graph.h"

Graph LoadData::loadGrafo(int num_ficheiro) const {
    ifstream f;
    string info;
    int n, t;
    int origem;
    int destino;
    int capacidade;
    int duracao;
    string n2, t2, o, de, c, du;

    if(num_ficheiro < 10) {
        f.open("in0"+to_string(num_ficheiro)+"_b.txt");
    }
    else {
        f.open("in"+to_string(num_ficheiro)+"_b.txt");
    }

    if (!f.is_open()) {
        cout << "Ficheiro nao existe." << endl;
        exit(0);
    }

    stringstream s(info);
    getline(f, n2, ' ');
    getline(f, t2, '\n');
    n = stoi(n2);
    t = stoi(t2);
    Graph g(n);
    while (getline(f, info)) {
        stringstream s(info);
        getline (s, o, ' ');
        getline (s, de, ' ');
        getline (s, c, ' ');
        getline (s, du, ' ');

        origem = stoi(o);
        destino = stoi(de);
        capacidade = stoi(c);
        duracao = stoi(du);

        if(g.isEmpty(origem))g.addParagem(origem);
        g.addEdge(origem, destino, capacidade, duracao);
    }
    f.close();
    return g;
}

Graph2 LoadData::loadGrafo2(int num_ficheiro) const {
    ifstream f;
    string info;
    int origem;
    int destino;
    int capacidade;
    string n2, t2, o, de, c;

    if(num_ficheiro < 10) {
        f.open("in0"+to_string(num_ficheiro)+"_b.txt");
    }
    else {
        f.open("in"+to_string(num_ficheiro)+"_b.txt");
    }

    if (!f.is_open()) {
        cout << "Ficheiro nao existe." << endl;
        exit(0);
    }

    stringstream s(info);
    getline(f, n2, ' ');
    getline(f, t2, '\n');
    Graph2 g(stoi(n2));
    while (getline(f, info)) {
        stringstream s(info);
        getline (s, o, ' ');
        getline (s, de, ' ');
        getline (s, c, ' ');

        origem = stoi(o);
        destino = stoi(de);
        capacidade = stoi(c);

        g.addLink(origem, destino, capacidade);
    }
    f.close();
    return g;
}