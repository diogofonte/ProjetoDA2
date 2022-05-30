#ifndef PROJETODA2_LOADDATA_H
#define PROJETODA2_LOADDATA_H

#include "Graph.h"

class LoadData {
public:
    Graph loadGrafo(int num_ficheiro) const;
    void loadGrafo2(vector<vector<int>> &g, int num_ficheiro) const;
};

#endif //PROJETODA2_LOADDATA_H
