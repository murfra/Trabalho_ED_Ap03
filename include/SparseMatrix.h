#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <stdexcept>
#include "Node.h"

class SparseMatrix
{
private:
    Node* m_head = new Node(0,0);    // inicializa o nó "sentinela" sem valor
    int linhas = 0;
    int colunas = 0;

public:
    SparseMatrix() = default;
    // Construtor da classe SparseMatrix
    // Essa função verifica se os valores de linha e coluna
    // (m e n respectivamente) são válidos e inicializa
    // (aloca espaço na memória) os nós sentinelas de
    // cada linha e coluna
    SparseMatrix(int m, int n);

    // Destrutor da classe SparseMatrix
    // Essa função apaga (desaloca a memória) os nós de
    // cada linha e coluna (m e n respectivamente) e
    // consequentemente a matriz
    ~SparseMatrix();

    void insert(int i, int j, double value);
    void print();
    void clear();

    double get(int i, int j);

    int getLines();
    int getCols();
    int size();

    SparseMatrix& operator=(const SparseMatrix& matriz);
};

#endif

