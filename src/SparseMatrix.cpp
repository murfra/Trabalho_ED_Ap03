#include "../include/SparseMatrix.h"
#include <iostream>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n)
{
    if (m < 0 && n < 0) throw std::runtime_error("Invalid line or column");
    m_head = new Node(0, 0);    // inicializa o nó "sentinela" sem valor

    // Inicilizando nós sentinela para cada linha m e coluna n
    for(unsigned short i = 1; i <= m+n; i++) {
        if (i <= n) { // inicilizando as colunas (0, n)
            Node *aux = new Node(0, i);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else { // inicilizando as linhas (m, 0);
            Node *aux = new Node(i-n, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
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

void SparseMatrix::print()
{
    Node* aux_d = m_head->direito;
    Node* aux_b = m_head->abaixo;


    for (int i = 0; i <= 3; i++)
    {
        std::cout << '(' << aux_d->linha << ", " << aux_d->coluna << ") "; // imprime (m, n)
        aux_d = aux_d->direito;
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << '(' << aux_b->linha << ", " << aux_b->coluna << ") " << std::endl; // imprime (m, n)
        aux_b = aux_b->abaixo;
    }

}
