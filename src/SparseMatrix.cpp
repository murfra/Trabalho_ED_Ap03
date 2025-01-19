#include "../include/SparseMatrix.h"

#include <iostream>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n) : linhas(m), colunas(n)
{
    if (m <= 0 && n <= 0) throw std::runtime_error("Invalid line or column");
  
    // Inicilizando nós sentinela para cada linha m e coluna n
    for(int i = m+n; i >= 1; i--)
    {
        if (i > n) // inicilizando as colunas (0, n)
        {
            Node *aux = new Node(0, i-n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else // inicilizando as linhas (m, 0);
        {
            Node *aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }

}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix() // Precisa ser terminada, por enquanto ela só apaga o nó principal
{
    delete m_head;
}

void SparseMatrix::insert(int i, int j, double value) // Acredito que dê pra melhorar
{
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) throw std::runtime_error("Invalid line or column");
    else if (value != 0)
    {
        Node *temp = new Node(i, j, value);
        Node *aux = m_head->direito;

        while (aux->coluna != j) aux = aux->direito; // move o aux até a coluna j
        temp->abaixo = aux->abaixo;
        aux->abaixo = temp;

        aux = m_head->abaixo; // redefine aux para começar da linha 1, coluna 0
        while (aux->linha != i) aux = aux->abaixo; // move o aux até a linha i
        
        // move até o último "direito", até a última coluna, no caso
        while (aux->direito->coluna != 0) aux = aux->direito;

        temp->direito = aux->direito; // faz temp apontar para onde aux apontava (o começo da linha)
        aux->direito = temp; // aponta o direito para o temp
    }
}

double SparseMatrix::get(int i, int j) // precisa ser implementada
{
    if (i <= 0 || i > linhas || j <= 0 || j > colunas) throw std::runtime_error("Invalid line or column");
    return 0;
}

void SparseMatrix::print() { // acredito que dê pra melhorar
    Node *aux = m_head->abaixo;

    for (int i = 1; i <= linhas; i++)
    {
        Node *temp = aux->direito; // pega o valor direito do aux, seria algo como m_head->abaixo->direito
        std::cout << "[ ";
        for (int j = 1; j <= colunas; j++)
        {
            if (temp->coluna == j) std::cout << temp->valor << " ";
            else std::cout << 0 << " ";

            if (j == temp->coluna) temp = temp->direito;
        }

        aux = aux->abaixo;
        std::cout << ']' << std::endl;
    }
}
