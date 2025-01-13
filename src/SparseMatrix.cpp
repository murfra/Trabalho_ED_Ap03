#include "../include/SparseMatrix.h"

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n)
{
    if (m < 0 && n < 0) throw std::runtime_error("Invalid line or column");
    m_head = new Node(m, n);    // inicializa o nó "sentinela" sem valor

    // Inicilizando nós sentinela para cada coluna n
    for (unsigned short i = 0; i < n; i++) {
        Node *aux = new Node(0, i);
        aux->direito = m_head->direito;
        m_head->direito = aux;
    }

    // Inicilizando nós sentinela para cada linha m
    for (unsigned short i = 0; i < m; i++) {
        Node *aux = new Node(m, 0);
        aux->abaixo = m_head->abaixo;
        m_head->abaixo = aux;
    }
}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix()
{
}

void SparseMatrix::insert(int m, int n, double value)
{
    if (m < 0 && n < 0) throw std::runtime_error("Invalid line or column");
    if (value != 0) m_head->valor = value;
}
