#include "../include/SparseMatrix.h"

#include <iostream>

// Implementação do construtor da classe
SparseMatrix::SparseMatrix(int m, int n)
{
    if (m < 0 && n < 0) throw std::runtime_error("Invalid line or column");
  
    // Inicilizando nós sentinela para cada linha m e coluna n
    for(unsigned short i = m+n; i >= 1; i--)
    {
        if (i > n) { // inicilizando as colunas (0, n)
            Node *aux = new Node(0, i-n);
            aux->direito = m_head->direito;
            m_head->direito = aux;
        }
        else { // inicilizando as linhas (m, 0);
            Node *aux = new Node(i, 0);
            aux->abaixo = m_head->abaixo;
            m_head->abaixo = aux;
        }
    }

}

// Implementação do destrutor da classe
SparseMatrix::~SparseMatrix()
{
}

void SparseMatrix::insert(int i, int j, double value) // Acredito que dê pra melhorar
{
    if (i < 0 && j < 0) throw std::runtime_error("Invalid line or column");
    if (value != 0)
    {
        Node *temp = new Node(i, j, value);
        Node *aux = m_head;
        Node *aux2 = m_head;

        while (aux->coluna != j) aux = aux->direito; // move o aux1 até a posição (0, n)
        temp->abaixo = aux->abaixo;
        aux->abaixo = temp;

        while (aux2->linha != i) aux2 = aux2->abaixo; // move o aux2 até a posição (m, 0)
        temp->direito = aux2->direito;
        aux2->direito = temp;

        /*std::cout << "Iserido!\ntemp->direito: " << '(' << temp->direito->linha*/
        /*          << ", " << temp->direito->coluna << "), temp->abaixo: "*/
        /*          << '(' << temp->abaixo->linha << ", " << temp->abaixo->coluna << ")\n";*/
    }
}

double SparseMatrix::get(int i, int j) { // precisa ser implementada
    if (i < 0 && j < 0) throw std::runtime_error("Invalid line or column");
    return 0;
}

void SparseMatrix::print() { // Não está certa
    Node* aux_d = m_head->direito->abaixo;

    for (int i = 1; i <= 3; i++) {
        std::cout << "[ ";
        for (int j = 1; j <= 3; j++) {
            if (aux_d->linha == i && aux_d->coluna == j && aux_d->valor) {
                std::cout << aux_d->valor << ' ';
                aux_d = aux_d->direito;
                continue;
            }
            std::cout << aux_d->valor << std::endl;
            aux_d = m_head->direito->abaixo->abaixo;

            std::cout << 0 << ' ';
        }
        std::cout << "]" << std::endl;
    }
}

// Função teste
void SparseMatrix::dbg_print()
{
    Node* aux_d = m_head;
    Node* aux_b = m_head->abaixo;


    for (int i = 0; i <= 3; i++)
    {
        std::cout << '(' << aux_d->linha << ", " << aux_d->coluna << ") "; // imprime (m, n)
        aux_d = aux_d->direito;
    }
    std::cout << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << '(' << aux_b->linha << ", " << aux_b->coluna << ") "; // imprime (m, n)
        if (aux_b->direito != 0) {
            std::cout << aux_b->direito->valor; // imprime (m, n)
        }
        std::cout << std::endl;
        aux_b = aux_b->abaixo;
    }
}
